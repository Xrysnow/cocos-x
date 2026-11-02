package org.cocos.lib;

import android.app.Activity;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.util.Log;
import android.view.Choreographer;
import android.view.Surface;

import java.util.ArrayDeque;
import java.util.concurrent.Callable;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;

/** Owns engine dispatch; gfx alone owns graphics contexts and presentation. */
final class CocosRenderHost implements Choreographer.FrameCallback {
    private static final String TAG = "CocosRenderHost";
    private static final AtomicLong NEXT_SESSION = new AtomicLong();
    private static final AtomicLong NEXT_SURFACE = new AtomicLong();
    private static final HandlerThread ENGINE_THREAD;
    private static final Handler ENGINE;
    private static volatile long animationInterval = 1000000000L / 60;
    private static volatile CocosRenderHost activeHost;
    // Engine lifetime survives Activity recreation. These two fields are engine-thread only.
    private static boolean engineInitialized;
    private static CocosRenderHost engineOwner;

    static {
        ENGINE_THREAD = new HandlerThread("CocosEngine");
        ENGINE_THREAD.start();
        ENGINE = new Handler(ENGINE_THREAD.getLooper());
    }

    private final Handler ui = new Handler(Looper.getMainLooper());
    private final Choreographer choreographer = Choreographer.getInstance();
    private final long session = NEXT_SESSION.incrementAndGet();
    private final AtomicBoolean frameQueued = new AtomicBoolean();
    private final ArrayDeque<Runnable> startupEvents = new ArrayDeque<>();
    private volatile long generation;
    private volatile boolean surfaceAlive;
    private volatile boolean ready;
    private volatile boolean resumed;
    private volatile boolean focused = true;
    private volatile boolean closed;
    private volatile long inputEpoch;
    private volatile long sizeRevision;
    private long attachedGeneration;
    private long failedGeneration;
    private boolean callbackScheduled;
    private long lastFrameTime;

    CocosRenderHost(Activity activity) {
        final CocosRenderHost previous = activeHost;
        if (previous != null) {
            previous.ready = false;
            previous.stopFrames();
        }
        activeHost = this;
        Log.i(TAG, "created session=" + session + " engineThread=" + ENGINE_THREAD.getId());
    }

    static void setAnimationInterval(float seconds) {
        if (Float.isNaN(seconds) || Float.isInfinite(seconds) || seconds < 0) return;
        animationInterval = (long) (seconds * 1000000000L);
    }

    void surfaceCreated() {
        if (!isCurrent()) return;
        generation = NEXT_SURFACE.incrementAndGet();
        inputEpoch++;
        surfaceAlive = true;
        ready = false;
        lastFrameTime = 0;
    }

    void surfaceChanged(Surface surface, int width, int height) {
        if (!isCurrent() || !surfaceAlive) return;
        final long current = generation;
        final long revision = ++sizeRevision;
        inputEpoch++;
        ready = false;
        stopFrames();
        ENGINE.post(() -> {
            if (!isCurrent() || !surfaceAlive || generation != current || sizeRevision != revision
                    || failedGeneration == current) return;
            engineOwner = this;
            final int result = attachedGeneration == current
                    ? nativeResize(session, current, width, height)
                    : nativeAttach(surface, session, current, width, height);
            if (result < 0) failedGeneration = current;
            if (result > 0) {
                attachedGeneration = current;
                engineInitialized = true;
                while (!startupEvents.isEmpty() && isCurrent()) startupEvents.removeFirst().run();
            }
            if (isCurrent() && surfaceAlive && generation == current && sizeRevision == revision) {
                ready = result > 0;
                if (ready) ui.post(this::scheduleFrame);
            }
        });
    }

    void surfaceDestroyed() {
        // Revoke permission before queuing the barrier, including an already queued frame.
        surfaceAlive = false;
        inputEpoch++;
        ready = false;
        stopFrames();
        final long current = generation;
        runControlAndWait("detach", () -> nativeDetach(session, current));
    }

    void setResumed(boolean value) {
        if (!isCurrent()) return;
        resumed = value;
        inputEpoch++;
        ENGINE.post(() -> {
            if (isCurrent()) {
                engineOwner = this;
                nativeSetResumed(session, value);
            }
        });
        if (value) scheduleFrame();
        else stopFrames();
    }

    void waitForPause() {
        runControlAndWait("pause", () -> {});
    }

    void close(boolean finalClose) {
        if (closed) return;
        surfaceAlive = false;
        ready = false;
        resumed = false;
        inputEpoch++;
        closed = true;
        final boolean ownsSession = activeHost == this;
        if (ownsSession) activeHost = null;
        stopFrames();
        final long current = generation;
        runControlAndWait("close", () -> {
            startupEvents.clear();
            nativeDetach(session, current);
            if (finalClose && ownsSession) {
                nativeClose(session);
                engineInitialized = false;
                engineOwner = null;
            }
        });
    }

    void queueEvent(Runnable event) {
        ENGINE.post(() -> {
            if (!isCurrent()) return;
            if (engineInitialized) event.run();
            else if (startupEvents.size() < 256) startupEvents.addLast(event);
            else Log.w(TAG, "startup queue full; event rejected session=" + session);
        });
    }

    void queueInput(Runnable event) {
        final long current = generation;
        final long epoch = inputEpoch;
        final long revision = sizeRevision;
        if (!isCurrent() || !resumed || !focused || !surfaceAlive) return;
        ENGINE.post(() -> {
            if (isCurrent() && ready && resumed && focused && surfaceAlive && current == generation
                    && epoch == inputEpoch && revision == sizeRevision) event.run();
        });
    }

    long getInputEpoch() {
        return inputEpoch;
    }

    boolean isInputCurrent(long epoch) {
        return isCurrent() && resumed && focused && ready && surfaceAlive && epoch == inputEpoch;
    }

    void cancelInput(Runnable cancel) {
        ENGINE.post(() -> {
            if (engineInitialized && engineOwner == this) cancel.run();
        });
    }

    void setFocused(boolean value) {
        focused = value;
        inputEpoch++;
    }

    boolean isCurrent() {
        return !closed && activeHost == this;
    }

    long getSession() {
        return session;
    }

    static void requireEngineThread() {
        if (Looper.myLooper() != ENGINE.getLooper())
            throw new IllegalStateException("Native/Lua callbacks require the CocosEngine thread");
    }

    /**
     * The only synchronous UI -> engine query is WebView's navigation veto.
     * It bypasses the startup/frame queue and always completes, including stale
     * sessions and exceptions (cancel navigation). While it runs, engine code
     * must use UI snapshots or asynchronous UI posts, never wait for the UI.
     */
    boolean decideNavigation(Callable<Boolean> decision) {
        final long current = generation;
        final boolean[] cancel = {true};
        runControlAndWait("navigation", () -> {
            if (!isCurrent() || !engineInitialized || !resumed || !surfaceAlive
                    || current != generation) return;
            try {
                requireEngineThread();
                cancel[0] = decision.call();
            } catch (Exception | LinkageError e) {
                Log.e(TAG, "navigation decision failed; cancelled session=" + session, e);
            }
        });
        return cancel[0];
    }

    private void scheduleFrame() {
        if (isCurrent() && resumed && ready && surfaceAlive && !callbackScheduled) {
            callbackScheduled = true;
            choreographer.postFrameCallback(this);
        }
    }

    private void stopFrames() {
        choreographer.removeFrameCallback(this);
        callbackScheduled = false;
    }

    @Override
    public void doFrame(long frameTimeNanos) {
        callbackScheduled = false;
        if (!isCurrent() || !resumed || !surfaceAlive) return;
        final long current = generation;
        final long revision = sizeRevision;
        final long interval = animationInterval;
        if (ready && (lastFrameTime == 0 || frameTimeNanos - lastFrameTime + 1000000L >= interval)
                && frameQueued.compareAndSet(false, true)) {
            // Retain the target cadence on displays whose refresh is not a multiple
            // of the requested frame rate; discard catch-up work after a long stall.
            lastFrameTime = lastFrameTime == 0 || interval == 0 || frameTimeNanos - lastFrameTime > interval * 4
                    ? frameTimeNanos : lastFrameTime + interval;
            ENGINE.post(() -> {
                try {
                    if (isCurrent() && resumed && ready && surfaceAlive && generation == current
                            && sizeRevision == revision) {
                        GameControllerAdapter.onDrawFrameStart();
                        if (nativeRender(session, current) < 0) {
                            failedGeneration = current;
                            ready = false;
                        }
                    }
                } finally {
                    frameQueued.set(false);
                }
            });
        }
        scheduleFrame();
    }

    private void runControlAndWait(String operation, Runnable task) {
        // Lifecycle barriers and navigation share the render/Lua engine looper.
        // "Control" is a queue role, never another thread that could enter Lua.
        if (Looper.myLooper() == ENGINE.getLooper()) {
            task.run();
            return;
        }
        final CountDownLatch complete = new CountDownLatch(1);
        final long started = System.nanoTime();
        ENGINE.post(() -> {
            try { task.run(); }
            finally { complete.countDown(); }
        });
        boolean interrupted = false;
        for (;;) {
            try {
                if (complete.await(2, TimeUnit.SECONDS)) break;
                // Diagnostic only: never return while gfx can still access the Surface.
                Log.e(TAG, "waiting operation=" + operation + " session=" + session
                        + " surface=" + generation + " elapsedMs=" + (System.nanoTime() - started) / 1000000);
            } catch (InterruptedException e) {
                interrupted = true;
            }
        }
        if (interrupted) Thread.currentThread().interrupt();
        Log.i(TAG, "confirmed operation=" + operation + " session=" + session + " surface=" + generation
                + " elapsedMs=" + (System.nanoTime() - started) / 1000000);
    }

    private static native int nativeAttach(Surface surface, long session, long generation, int width, int height);
    private static native int nativeResize(long session, long generation, int width, int height);
    private static native void nativeDetach(long session, long generation);
    private static native void nativeSetResumed(long session, boolean resumed);
    private static native int nativeRender(long session, long generation);
    private static native void nativeClose(long session);
}
