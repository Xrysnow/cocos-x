package org.cocos.lib;

import android.app.Activity;
import android.graphics.Color;
import android.media.AudioAttributes;
import android.media.MediaPlayer;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.system.Os;
import android.system.OsConstants;
import android.util.Log;
import android.util.SparseArray;
import android.view.Gravity;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import java.io.File;
import java.io.FileInputStream;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

/** Native video overlays. MediaPlayer and View state belong exclusively to UI. */
public final class VideoHelper {
    private static final String TAG = "VideoHelper";
    private static final int PLAYING = 0, PAUSED = 1, STOPPED = 2, COMPLETED = 3, ERROR = 4;
    private static final Handler UI = new Handler(Looper.getMainLooper());
    private static final ConcurrentHashMap<Integer, Ticket> tickets = new ConcurrentHashMap<>();
    private static final SparseArray<Entry> entries = new SparseArray<>();
    private static final AtomicLong hostEpoch = new AtomicLong();
    private static CocosActivity activity;
    private static FrameLayout layout;
    private static boolean resumed;
    private static final View.OnLayoutChangeListener layoutListener =
            (view, l, t, r, b, oldL, oldT, oldR, oldB) -> layoutAll();

    private VideoHelper() {}

    private static final class Ticket {
        final int id;
        volatile long generation;
        volatile long fullScreenRevision;
        volatile Entry entry;
        Ticket(int id) { this.id = id; }
    }

    // Retained across Activity recreation; View and MediaPlayer are released on unbind.
    private static final class Entry {
        final Ticket ticket;
        long generation;
        long fullScreenRevision;
        long playerSerial;
        String path = "";
        long positionMs;
        Long pendingSeek;
        boolean seekInFlight;
        boolean prepared;
        boolean wantsPlay;
        boolean completed;
        boolean failed;
        boolean visible;
        boolean looping;
        boolean keepRatio;
        boolean inputEnabled = true;
        boolean fullScreen;
        int x, y, width, height;
        int videoWidth, videoHeight;
        MediaPlayer player;
        VideoView view;

        Entry(Ticket ticket) { this.ticket = ticket; }
    }

    interface Mutation { void run(Entry entry); }

    private static boolean alive(Ticket ticket) { return tickets.get(ticket.id) == ticket; }

    // Commands remain ordered during Activity handoff. They mutate descriptors even
    // while no UI host exists, and never wait for the CocosEngine thread.
    private static void mutate(int id, Mutation mutation) {
        final Ticket ticket = tickets.get(id);
        if (ticket == null) return;
        UI.post(() -> {
            final Entry entry = entries.get(id);
            if (alive(ticket) && entry != null && entry.ticket == ticket) mutation.run(entry);
        });
    }

    private static void mutate(int id, long generation, Mutation mutation) {
        final Ticket ticket = tickets.get(id);
        if (ticket == null) return;
        ticket.generation = generation;
        UI.post(() -> {
            final Entry entry = entries.get(id);
            if (!alive(ticket) || entry == null || entry.ticket != ticket) return;
            entry.generation = generation;
            mutation.run(entry);
        });
    }

    static void bind(CocosActivity owner, FrameLayout root) {
        if (activity != null) unbind(activity, true);
        activity = owner;
        layout = root;
        resumed = false;
        hostEpoch.incrementAndGet();
        root.addOnLayoutChangeListener(layoutListener);
        for (int i = 0; i < entries.size(); ++i) attach(entries.valueAt(i));
    }

    static void unbind(Activity owner, boolean retain) {
        if (activity != owner) return;
        hostEpoch.incrementAndGet();
        resumed = false;
        if (layout != null) layout.removeOnLayoutChangeListener(layoutListener);
        for (int i = 0; i < entries.size(); ++i) detach(entries.valueAt(i));
        activity = null;
        layout = null;
        if (!retain) {
            entries.clear();
            tickets.clear();
        }
    }

    static void setResumed(Activity owner, boolean value) {
        if (activity != owner) return;
        resumed = value;
        for (int i = 0; i < entries.size(); ++i) applyPlayback(entries.valueAt(i));
    }

    static boolean handleBack(Activity owner) {
        if (activity != owner) return false;
        for (int i = entries.size() - 1; i >= 0; --i) {
            final Entry entry = entries.valueAt(i);
            if (entry.fullScreen && entry.visible) {
                entry.fullScreen = false;
                updateLayout(entry);
                emitExitFullScreen(entry);
                return true;
            }
        }
        return false;
    }

    static boolean hasFullScreen(Activity owner) {
        if (activity != owner) return false;
        for (int i = entries.size() - 1; i >= 0; --i)
            if (entries.valueAt(i).fullScreen && entries.valueAt(i).visible) return true;
        return false;
    }

    public static void createVideoWidget(int id) {
        if (id < 0) return;
        final Ticket ticket = new Ticket(id);
        if (tickets.putIfAbsent(id, ticket) != null) return;
        UI.post(() -> {
            if (!alive(ticket)) return;
            final Entry entry = new Entry(ticket);
            ticket.entry = entry;
            entries.put(id, entry);
            attach(entry);
        });
    }

    public static void removeVideoWidget(int id) {
        final Ticket ticket = tickets.remove(id);
        if (ticket == null) return;
        UI.post(() -> {
            final Entry entry = entries.get(id);
            if (entry != null && entry.ticket == ticket) {
                detach(entry);
                entries.remove(id);
                ticket.entry = null;
            }
        });
    }

    public static void setVideoFile(int id, String path, long generation) {
        mutate(id, generation, entry -> {
            releasePlayer(entry, false);
            entry.path = path == null ? "" : path;
            entry.positionMs = 0;
            entry.pendingSeek = null;
            entry.wantsPlay = false;
            entry.completed = false;
            entry.failed = false;
            entry.videoWidth = entry.videoHeight = 0;
            if (!isLocalFile(entry.path)) fail(entry, "Only ordinary local files are supported", null);
            else open(entry);
        });
    }

    public static void startVideo(int id, long generation) {
        mutate(id, generation, entry -> {
            entry.wantsPlay = true;
            entry.completed = false;
            entry.positionMs = 0;
            entry.pendingSeek = 0L;
            if (entry.failed) entry.failed = false;
            if (!isLocalFile(entry.path)) {
                fail(entry, "Only ordinary local files are supported", null);
                return;
            }
            open(entry);
            seekIfNeeded(entry);
            applyPlayback(entry);
        });
    }

    public static void pauseVideo(int id, long generation) {
        mutate(id, generation, entry -> {
            entry.wantsPlay = false;
            if (!applyPlayback(entry)) emit(entry, PAUSED);
        });
    }

    public static void resumeVideo(int id, long generation) {
        mutate(id, generation, entry -> {
            entry.wantsPlay = true;
            if (entry.completed) {
                entry.completed = false;
                entry.pendingSeek = 0L;
                entry.positionMs = 0;
            }
            if (entry.failed) entry.failed = false;
            if (!isLocalFile(entry.path)) {
                fail(entry, "Only ordinary local files are supported", null);
                return;
            }
            open(entry);
            seekIfNeeded(entry);
            if (!applyPlayback(entry) && !entry.failed) {
                // Each native resume has a new generation. Confirm unchanged
                // state too, since its previous notification may now be stale.
                try {
                    final boolean playing = entry.prepared && entry.player != null && !entry.seekInFlight
                            && entry.pendingSeek == null && entry.player.isPlaying();
                    emit(entry, playing ? PLAYING : PAUSED);
                } catch (IllegalStateException exception) { fail(entry, "Video resume failed", exception); }
            }
        });
    }

    public static void stopVideo(int id, long generation) {
        mutate(id, generation, entry -> {
            entry.wantsPlay = false;
            entry.completed = false;
            requestSeek(entry, 0);
            emit(entry, STOPPED);
        });
    }

    public static void seekVideoTo(int id, long generation, long milliseconds) {
        mutate(id, generation, entry -> {
            if (milliseconds < 0) return;
            entry.completed = false;
            requestSeek(entry, milliseconds);
        });
    }

    public static void setVideoVisible(int id, boolean visible) {
        mutate(id, entry -> {
            entry.visible = visible;
            if (entry.view != null) entry.view.setVisibility(visible ? View.VISIBLE : View.GONE);
            applyPlayback(entry);
        });
    }

    public static void setVideoRect(int id, int x, int y, int width, int height) {
        mutate(id, entry -> {
            entry.x = x;
            entry.y = y;
            entry.width = Math.max(0, width);
            entry.height = Math.max(0, height);
            updateLayout(entry);
        });
    }

    public static void setFullScreenEnabled(int id, boolean enabled, long revision) {
        final Ticket ticket = tickets.get(id);
        if (ticket == null) return;
        ticket.fullScreenRevision = revision;
        UI.post(() -> {
            final Entry entry = entries.get(id);
            if (!alive(ticket) || entry == null || entry.ticket != ticket) return;
            entry.fullScreenRevision = revision;
            entry.fullScreen = enabled;
            updateLayout(entry);
        });
    }

    public static void setVideoKeepRatioEnabled(int id, boolean enabled) {
        mutate(id, entry -> { entry.keepRatio = enabled; updateLayout(entry); });
    }

    public static void setLooping(int id, boolean looping) {
        mutate(id, entry -> {
            entry.looping = looping;
            if (entry.player != null && entry.prepared) {
                try { entry.player.setLooping(looping); }
                catch (IllegalStateException exception) { fail(entry, "setLooping failed", exception); }
            }
        });
    }

    public static void setUserInputEnabled(int id, boolean enabled) {
        mutate(id, entry -> {
            entry.inputEnabled = enabled;
            if (entry.view != null) entry.view.setClickable(enabled);
        });
    }

    private static boolean isLocalFile(String path) {
        if (path.isEmpty() || path.contains("://")) return false;
        final File file = new File(path);
        return file.isAbsolute() && file.isFile();
    }

    private static void attach(Entry entry) {
        if (activity == null || layout == null || !alive(entry.ticket)) return;
        entry.view = new VideoView(activity, entry);
        entry.view.setVisibility(entry.visible ? View.VISIBLE : View.GONE);
        layout.addView(entry.view, new FrameLayout.LayoutParams(0, 0));
        updateLayout(entry);
    }

    private static void detach(Entry entry) {
        releasePlayer(entry, true);
        if (entry.view != null) {
            final VideoView view = entry.view;
            entry.view = null;
            if (view.getParent() instanceof ViewGroup) ((ViewGroup) view.getParent()).removeView(view);
        }
    }

    private static void layoutAll() {
        for (int i = 0; i < entries.size(); ++i) updateLayout(entries.valueAt(i));
    }

    private static void updateLayout(Entry entry) {
        if (entry.view == null || layout == null || activity == null) return;
        final FrameLayout.LayoutParams params;
        if (entry.fullScreen) {
            params = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.MATCH_PARENT);
        } else {
            params = new FrameLayout.LayoutParams(entry.width, entry.height, Gravity.TOP | Gravity.LEFT);
            final int[] rootOrigin = new int[2];
            final int[] renderOrigin = new int[2];
            layout.getLocationInWindow(rootOrigin);
            activity.getGLSurfaceView().getLocationInWindow(renderOrigin);
            params.leftMargin = entry.x + renderOrigin[0] - rootOrigin[0];
            params.topMargin = entry.y + renderOrigin[1] - rootOrigin[1];
        }
        entry.view.setLayoutParams(params);
        entry.view.updateSurfaceLayout();
    }

    private static boolean current(Entry entry, MediaPlayer player, long serial, long epoch) {
        return alive(entry.ticket) && entries.get(entry.ticket.id) == entry && entry.player == player
                && entry.playerSerial == serial && hostEpoch.get() == epoch && activity != null;
    }

    private static void open(Entry entry) {
        if (entry.player != null || entry.failed || entry.path.isEmpty() || entry.view == null
                || !entry.view.surfaceAlive || activity == null) return;
        final MediaPlayer player;
        try { player = new MediaPlayer(); }
        catch (RuntimeException exception) {
            fail(entry, "Cannot create MediaPlayer", exception);
            return;
        }
        entry.player = player;
        entry.prepared = false;
        entry.seekInFlight = false;
        final long serial = ++entry.playerSerial;
        final long epoch = hostEpoch.get();
        try (FileInputStream input = new FileInputStream(entry.path)) {
            if (!OsConstants.S_ISREG(Os.fstat(input.getFD()).st_mode))
                throw new IllegalArgumentException("Video source must be an ordinary local file");
            player.setAudioAttributes(new AudioAttributes.Builder().setUsage(AudioAttributes.USAGE_MEDIA)
                    .setContentType(AudioAttributes.CONTENT_TYPE_MOVIE).build());
            player.setDisplay(entry.view.surface.getHolder());
            player.setDataSource(input.getFD());
            player.setLooping(entry.looping);
            player.setOnPreparedListener(prepared -> {
                if (!current(entry, player, serial, epoch)) return;
                try {
                    entry.prepared = true;
                    player.setLooping(entry.looping);
                    entry.videoWidth = player.getVideoWidth();
                    entry.videoHeight = player.getVideoHeight();
                    updateLayout(entry);
                    if (entry.pendingSeek == null && entry.positionMs > 0) entry.pendingSeek = entry.positionMs;
                    seekIfNeeded(entry);
                    applyPlayback(entry);
                } catch (IllegalStateException exception) { fail(entry, "Video preparation failed", exception); }
            });
            player.setOnVideoSizeChangedListener((changed, width, height) -> {
                if (!current(entry, player, serial, epoch)) return;
                entry.videoWidth = width;
                entry.videoHeight = height;
                updateLayout(entry);
            });
            player.setOnSeekCompleteListener(seeked -> {
                if (!current(entry, player, serial, epoch) || !entry.seekInFlight) return;
                entry.seekInFlight = false;
                seekIfNeeded(entry);
                applyPlayback(entry);
            });
            player.setOnCompletionListener(completed -> {
                if (!current(entry, player, serial, epoch) || entry.seekInFlight || entry.pendingSeek != null
                        || !entry.wantsPlay || entry.generation != entry.ticket.generation) return;
                try {
                    entry.wantsPlay = false;
                    entry.completed = true;
                    entry.positionMs = Math.max(0, player.getDuration());
                    if (entry.view != null) entry.view.setKeepScreenOn(false);
                    emit(entry, COMPLETED);
                } catch (IllegalStateException exception) { fail(entry, "Video completion failed", exception); }
            });
            player.setOnErrorListener((failed, what, extra) -> {
                if (current(entry, player, serial, epoch)) fail(entry,
                        "MediaPlayer error " + what + "/" + extra, null);
                return true;
            });
            player.prepareAsync();
        } catch (Exception exception) {
            if (current(entry, player, serial, epoch)) fail(entry, "Cannot open video file", exception);
        }
    }

    private static void requestSeek(Entry entry, long milliseconds) {
        entry.positionMs = milliseconds;
        entry.pendingSeek = milliseconds;
        seekIfNeeded(entry);
        applyPlayback(entry);
    }

    private static void seekIfNeeded(Entry entry) {
        if (!entry.prepared || entry.player == null || entry.seekInFlight || entry.pendingSeek == null) return;
        try {
            if (entry.player.isPlaying()) entry.player.pause();
            final long target = Math.min(entry.pendingSeek, Math.max(0, entry.player.getDuration()));
            entry.pendingSeek = null;
            entry.positionMs = target;
            entry.seekInFlight = true;
            if (Build.VERSION.SDK_INT >= 26) entry.player.seekTo(target, MediaPlayer.SEEK_CLOSEST);
            else entry.player.seekTo((int) Math.min(target, Integer.MAX_VALUE));
        } catch (IllegalStateException exception) { fail(entry, "Video seek failed", exception); }
    }

    private static boolean applyPlayback(Entry entry) {
        if (!entry.prepared || entry.player == null) return false;
        final boolean shouldPlay = resumed && entry.visible && entry.wantsPlay && !entry.seekInFlight
                && entry.pendingSeek == null && entry.view != null && entry.view.surfaceAlive;
        // A newer native control may be queued behind a MediaPlayer callback.
        // Keep preparation/seek bookkeeping, but do not start its older intent.
        // Lifecycle and scene gates can still pause output immediately.
        if (shouldPlay && entry.generation != entry.ticket.generation) return false;
        try {
            final boolean playing = entry.player.isPlaying();
            final boolean changed = shouldPlay != playing;
            if (shouldPlay && !playing) {
                entry.player.start();
                emit(entry, PLAYING);
            } else if (!shouldPlay && playing) {
                entry.player.pause();
                entry.positionMs = entry.player.getCurrentPosition();
                emit(entry, PAUSED);
            }
            if (entry.view != null) entry.view.setKeepScreenOn(shouldPlay);
            return changed;
        } catch (IllegalStateException exception) { fail(entry, "Video playback control failed", exception); }
        return false;
    }

    private static void releasePlayer(Entry entry, boolean savePosition) {
        final MediaPlayer player = entry.player;
        if (player != null) {
            if (savePosition && entry.prepared && !entry.seekInFlight && entry.pendingSeek == null) {
                try { entry.positionMs = Math.max(0, player.getCurrentPosition()); }
                catch (IllegalStateException ignored) { }
            }
            entry.player = null;
            ++entry.playerSerial;
            player.setOnPreparedListener(null);
            player.setOnSeekCompleteListener(null);
            player.setOnCompletionListener(null);
            player.setOnErrorListener(null);
            player.setOnVideoSizeChangedListener(null);
            player.release();
        }
        entry.prepared = false;
        entry.seekInFlight = false;
        if (entry.view != null) entry.view.setKeepScreenOn(false);
    }

    private static void fail(Entry entry, String message, Exception exception) {
        if (entry.failed) return;
        Log.e(TAG, message + " id=" + entry.ticket.id + " generation=" + entry.generation, exception);
        entry.failed = true;
        entry.wantsPlay = false;
        releasePlayer(entry, false);
        emit(entry, ERROR);
    }

    private static void emit(Entry entry, int event) {
        final Ticket ticket = entry.ticket;
        final long generation = entry.generation;
        final long epoch = hostEpoch.get();
        if (!alive(ticket) || ticket.generation != generation || activity == null) return;
        CocosEngine.runOnGLThread(() -> {
            if (alive(ticket) && ticket.entry == entry && ticket.generation == generation && hostEpoch.get() == epoch) {
                CocosRenderHost.requireEngineThread();
                nativeExecuteVideoCallback(ticket.id, generation, event);
            }
        });
    }

    private static native void nativeExecuteVideoCallback(int id, long generation, int event);

    private static void emitExitFullScreen(Entry entry) {
        final Ticket ticket = entry.ticket;
        final long revision = entry.fullScreenRevision;
        final long epoch = hostEpoch.get();
        if (!alive(ticket) || ticket.fullScreenRevision != revision
                || activity == null) return;
        CocosEngine.runOnGLThread(() -> {
            if (alive(ticket) && ticket.entry == entry && ticket.fullScreenRevision == revision
                    && hostEpoch.get() == epoch) {
                CocosRenderHost.requireEngineThread();
                nativeExitFullScreen(ticket.id, revision);
            }
        });
    }

    private static native void nativeExitFullScreen(int id, long revision);

    private static final class VideoView extends FrameLayout implements SurfaceHolder.Callback {
        final Entry entry;
        final SurfaceView surface;
        boolean surfaceAlive;

        VideoView(CocosActivity owner, Entry entry) {
            super(owner);
            this.entry = entry;
            setBackgroundColor(Color.BLACK);
            surface = new SurfaceView(owner);
            surface.setZOrderMediaOverlay(true);
            surface.getHolder().addCallback(this);
            addView(surface, new FrameLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
            setOnClickListener(view -> {
                if (!entry.inputEnabled || entry.view != this) return;
                entry.wantsPlay = !entry.wantsPlay;
                if (entry.wantsPlay && entry.completed) {
                    entry.completed = false;
                    requestSeek(entry, 0);
                }
                applyPlayback(entry);
            });
            setClickable(entry.inputEnabled);
        }

        @Override protected void onSizeChanged(int width, int height, int oldWidth, int oldHeight) {
            super.onSizeChanged(width, height, oldWidth, oldHeight);
            updateSurfaceLayout();
        }

        void updateSurfaceLayout() {
            int width = getWidth(), height = getHeight();
            if (entry.keepRatio && entry.videoWidth > 0 && entry.videoHeight > 0 && width > 0 && height > 0) {
                final double scale = Math.min((double) width / entry.videoWidth, (double) height / entry.videoHeight);
                width = Math.max(1, (int) Math.round(entry.videoWidth * scale));
                height = Math.max(1, (int) Math.round(entry.videoHeight * scale));
                surface.setLayoutParams(new FrameLayout.LayoutParams(width, height, Gravity.CENTER));
            } else {
                surface.setLayoutParams(new FrameLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
            }
        }

        @Override public void surfaceCreated(SurfaceHolder holder) {
            if (entry.view != this) return;
            surfaceAlive = true;
            open(entry);
        }

        @Override public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
            if (entry.view == this) applyPlayback(entry);
        }

        @Override public void surfaceDestroyed(SurfaceHolder holder) {
            surfaceAlive = false;
            if (entry.view == this) releasePlayer(entry, true);
        }
    }
}
