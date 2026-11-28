package org.cocos.lib;

import android.app.NotificationManager;
import android.content.Context;
import android.database.ContentObserver;
import android.media.AudioAttributes;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.os.VibrationAttributes;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.os.VibratorManager;
import android.provider.Settings;
import android.view.InputDevice;
import java.lang.reflect.Method;
import java.util.ArrayDeque;
import java.util.Arrays;

/** One immutable Vibrator handle per published connection. Called from its native serial worker. */
public final class CocosHaptics
{
    private static final int OK = 0, UNSUPPORTED = 1, DISCONNECTED = 2, BUSY = 3, DENIED = 4, INVALID = 5, FAILED = 7,
                             SILENT        = 256, ORIGINAL_DECLINED = 257;
    private static final int HANDSET       = -1;
    private static final String FORWARDING = "vibrate_input_devices";
    private static final AudioAttributes GAME =
            new AudioAttributes.Builder().setUsage(AudioAttributes.USAGE_GAME).build();
    private static volatile Context context;
    private static volatile boolean active;
    private static ContentObserver observer;
    private final Vibrator vibrator;
    private final int deviceId;
    private final String descriptor;
    private final int stopBoundMs;
    private final CocosHapticsHe he;
    // Reserve 30 ms for a 12 ms pulse, including stretching observed in system playback history.
    private static final int BINARY_ON_BUDGET_MS = 30;
    private boolean delivered, standardActive, heFailed;
    private boolean heV2Allowed;
    private String lastRoute;

    private void route(String name)
    {
        if (!name.equals(lastRoute))
        {
            android.util.Log.i("CocosHaptics", "preset route=" + name);
            lastRoute = name;
        }
    }

    // HE exposes no usage parameter. Respect the public feedback switch and interruption filter.
    private static boolean permitsHe(Context app)
    {
        try
        {
            NotificationManager notifications = app.getSystemService(NotificationManager.class);
            return notifications != null && notifications.getCurrentInterruptionFilter() == NotificationManager.INTERRUPTION_FILTER_ALL
                    && Settings.System.getInt(app.getContentResolver(), Settings.System.HAPTIC_FEEDBACK_ENABLED, 0) != 0;
        }
        catch (RuntimeException unavailable)
        {
            return false;
        }
    }

    private static boolean includesBuild(android.os.Bundle metadata, String key, String build)
    {
        String builds = metadata == null ? null : metadata.getString(key);
        return builds != null && Arrays.asList(builds.split(";")).contains(build);
    }

    private CocosHapticsHe openHe(Context app)
    {
        // Hosts opt in by firmware AND target SDK, then may disable it between sessions.
        try
        {
            android.content.pm.ApplicationInfo info = app.getPackageManager().getApplicationInfo(
                    app.getPackageName(), android.content.pm.PackageManager.GET_META_DATA);
            String build = Build.FINGERPRINT + "|" + info.targetSdkVersion;
            if (!includesBuild(info.metaData, "org.cocos.lib.haptics.heBuilds", build)
                    || !app.getSharedPreferences("cocos_haptics", Context.MODE_PRIVATE).getBoolean("he_enabled", false))
                return null;
            // Qualify formats independently. Existing v1-only hosts keep their tested capabilities.
            heV2Allowed = includesBuild(info.metaData, "org.cocos.lib.haptics.heV2Builds", build)
                    && app.getSharedPreferences("cocos_haptics", Context.MODE_PRIVATE).getBoolean("he_v2_enabled", true);
            CocosHapticsHe adapter = CocosHapticsHe.open();
            android.util.Log.i("CocosHaptics", "HE probe=" + (adapter == null ? "unavailable" : "available"));
            return adapter;
        }
        catch (android.content.pm.PackageManager.NameNotFoundException | ReflectiveOperationException
                | RuntimeException | LinkageError unavailable)
        {
            android.util.Log.i("CocosHaptics", "HE probe unavailable: " + unavailable.getClass().getSimpleName());
            return null;
        }
    }
    private final ArrayDeque<Long> binaryOn = new ArrayDeque<>();
    private long nextBinaryOn;
    private CocosHaptics(Vibrator v, int id, String name)
    {
        vibrator    = v;
        deviceId    = id;
        descriptor  = name;
        he = id == HANDSET ? openHe(context) : null;
        stopBoundMs = he == null ? verifiedStopBound(id == HANDSET ? "handset" : name) : 0;
    }
    // App-packaged measurements name an exact OS build and actuator. A build
    // update or an unknown controller therefore falls back to preset-only output.
    private static int verifiedStopBound(String route)
    {
        Context app = context;
        int res     = app.getResources().getIdentifier("cocos_haptic_stop_bounds", "array", app.getPackageName());
        if (res == 0)
            return 0;
        String prefix = Build.FINGERPRINT + "|" + route + "|";
        for (String entry : app.getResources().getStringArray(res))
            if (entry.startsWith(prefix))
            {
                try
                {
                    int ms = Integer.parseInt(entry.substring(prefix.length()));
                    return ms > 0 && ms <= 180 ? ms : 0;
                }
                catch (NumberFormatException ignored)
                {
                    return 0;
                }
            }
        return 0;
    }
    static synchronized void init(Context app)
    {
        if (context == app)
            return;
        if (context != null && observer != null)
            context.getContentResolver().unregisterContentObserver(observer);
        context  = app;
        observer = new ContentObserver(new Handler(Looper.getMainLooper())) {
            @Override
            public void onChange(boolean selfChange)
            {
                nativeRouting(forwarding());
            }
        };
        try
        {
            app.getContentResolver().registerContentObserver(Settings.System.getUriFor(FORWARDING), false, observer);
        }
        catch (SecurityException ignored)
        {
            observer = null;
        }
    }
    private static boolean forwarding()
    {
        try
        {
            return Settings.System.getInt(context.getContentResolver(), FORWARDING, 0) != 0;
        }
        catch (RuntimeException unavailable)
        {
            return true;
        }
    }
    static void focus(boolean value)
    {
        active = value;
        nativeFocus(value);
    }
    private static native boolean nativePermitted();
    static native void nativeFocus(boolean active);
    static native void nativeRouting(boolean forwarded);
    static native void nativeVibrate(float seconds);
    static CocosHaptics open(int id)
    {
        Context app = context;
        if (app == null)
            return null;
        try
        {
            Vibrator v;
            String name = "";
            if (id != HANDSET)
            {
                InputDevice pad = InputDevice.getDevice(id);
                if (pad == null)
                    return null;
                name = pad.getDescriptor();
                v    = Build.VERSION.SDK_INT >= 31 ? pad.getVibratorManager().getDefaultVibrator() : pad.getVibrator();
            }
            else if (Build.VERSION.SDK_INT >= 31)
            {
                VibratorManager manager = app.getSystemService(VibratorManager.class);
                if (manager == null)
                    return null;
                v = manager.getDefaultVibrator();
            }
            else
                v = (Vibrator) app.getSystemService(Context.VIBRATOR_SERVICE);
            return v != null && v.hasVibrator() ? new CocosHaptics(v, id, name) : null;
        }
        catch (RuntimeException unavailable)
        {
            return null;
        }
    }
    private Object envelope(String name, Class<?>[] types, Object... args)
    {
        if (Build.VERSION.SDK_INT < 36)
            return null;
        try
        {
            Class<?> adapter = Class.forName("org.cocos.lib.CocosHapticsEnvelope");
            Method method    = adapter.getMethod(name, types);
            return method.invoke(null, args);
        }
        catch (ReflectiveOperationException | LinkageError unavailable)
        {
            return null;
        }
    }
    int capabilities()
    {
        // The build flag can be read on old Android without linking API 36 classes.
        int envelopeFlags = !BuildConfig.HAPTICS_ENVELOPE_BUILT ? 16 : Build.VERSION.SDK_INT < 36 ? 32
                : envelope("limits", new Class[] {Vibrator.class}, vibrator) != null ? 2 : 64;
        return (Build.VERSION.SDK_INT >= 26 && vibrator.hasAmplitudeControl() ? 1 : 0) | envelopeFlags
                | (deviceId == HANDSET && forwarding() ? 4 : 0) | (stopBoundMs > 0 ? 8 : 0)
                | (he != null ? 128 : 0) | (he != null && heV2Allowed ? 256 : 0);
    }
    // Store the time of each approved on-millisecond across native batch boundaries.
    private long[] binary(long[] durations, int[] amps)
    {
        int size = 0;
        for (long d : durations)
        {
            if (d < 0 || d > 1000 - size)
                throw new IllegalArgumentException();
            size += (int) d;
        }
        int pulseBudget = deviceId == HANDSET ? BINARY_ON_BUDGET_MS : 12;
        boolean[] on  = new boolean[size];
        long origin   = SystemClock.elapsedRealtime();
        int cursor    = 0;
        double credit = 0;
        boolean above = false;
        int expansionMs = 0;
        for (int i = 0; i < amps.length; i++)
        {
            int a        = amps[i] < 0 ? 255 : amps[i];
            double level = a / 255.0;
            above        = level >= (above ? .16 : .24);
            for (int j = 0; j < durations[i]; j++, cursor++)
            {
                if (!above)
                {
                    credit = 0;
                    continue;
                }
                credit   = Math.min(Math.max(24, pulseBudget), credit + level * level);
                long now = origin + cursor + expansionMs;
                while (!binaryOn.isEmpty() && binaryOn.peekFirst() <= now - 250) binaryOn.removeFirst();
                if (credit >= pulseBudget && now >= nextBinaryOn
                        && durations[i] - j >= expansionMs + pulseBudget && binaryOn.size() + pulseBudget <= 80)
                {
                    for (int k = 0; k < 12; k++)
                        on[cursor + k] = true;
                    for (int k = 0; k < pulseBudget; ++k)
                        binaryOn.addLast(now + k);
                    credit -= pulseBudget;
                    expansionMs += pulseBudget - 12;
                    nextBinaryOn = now + pulseBudget + 16;
                }
            }
        }
        long[] alternating = new long[129];
        int slot           = 0;
        for (boolean v : on)
        {
            if (v != ((slot & 1) != 0))
            {
                if (++slot == alternating.length)
                    return null;
            }
            alternating[slot]++;
        }
        return slot == 0 ? null : Arrays.copyOf(alternating, slot + 1);
    }
    private void requirePermit()
    {
        if (!active || !nativePermitted())
            throw new java.util.concurrent.CancellationException();
    }
    private void play(VibrationEffect effect)
    {
        requirePermit();
        delivered = true;
        standardActive = true;
        if (Build.VERSION.SDK_INT >= 33)
            vibrator.vibrate(effect, VibrationAttributes.createForUsage(VibrationAttributes.USAGE_MEDIA));
        else
            vibrator.vibrate(effect, GAME);
    }
    // The controller retains the writer while a finite asynchronous HE effect
    // drains. Public waveforms need no additional HE startup allowance.
    int executeQueued(int kind, long[] durations, int[] amplitudes, float[] values)
    {
        int result = execute(kind, durations, amplitudes, values);
        return result == OK && kind == 0 && he != null && he.playing() ? 258 : result;
    }
    // kind 0 is a mixed preset; 1-4 preserve native Raw input exactly.
    int execute(int kind, long[] durations, int[] amplitudes, float[] values)
    {
        if (!active)
            return BUSY;
        if (deviceId != HANDSET)
        {
            InputDevice pad = InputDevice.getDevice(deviceId);
            if (pad == null || !descriptor.equals(pad.getDescriptor()))
                return DISCONNECTED;
        }
        try
        {
            if (kind != 0 && delivered)
            {
                int previous = stop();
                if (previous != OK)
                    return previous;
                if (!active)
                    return BUSY;
            }
            if (kind == 3)
            {
                if (Build.VERSION.SDK_INT < 31)
                    return UNSUPPORTED;
                boolean[] supported           = vibrator.arePrimitivesSupported(amplitudes);
                int[] lengths                 = vibrator.getPrimitiveDurations(amplitudes);
                long span                     = 0;
                VibrationEffect.Composition c = VibrationEffect.startComposition();
                for (int i = 0; i < amplitudes.length; i++)
                {
                    if (!supported[i] || lengths[i] <= 0)
                        return UNSUPPORTED;
                    span += durations[i] + lengths[i];
                    if (span > 1000)
                        return INVALID;
                    c.addPrimitive(amplitudes[i], values[i], (int) durations[i]);
                }
                play(c.compose());
                return OK;
            }
            if (kind == 4 || kind == 5)
            {
                int n       = durations.length;
                float[] amp = Arrays.copyOfRange(values, 0, n), texture = Arrays.copyOfRange(values, n, n * 2);
                VibrationEffect effect = (VibrationEffect) envelope(
                        "raw",
                        new Class[] {Vibrator.class, boolean.class, long[].class, float[].class, float[].class},
                        vibrator,
                        kind == 5,
                        durations,
                        amp,
                        texture);
                if (effect == null)
                    return UNSUPPORTED;
                play(effect);
                return OK;
            }
            // An open-ended bed may continue in the next batch. Its native envelope would force a dip to zero.
            boolean openBed = kind == 0 && amplitudes.length > 0 && amplitudes[amplitudes.length - 1] > 0
                    && Build.VERSION.SDK_INT >= 26 && vibrator.hasAmplitudeControl();
            if (kind == 0 && (he == null || !he.playing()) && BuildConfig.HAPTICS_ENVELOPE_BUILT
                    && Build.VERSION.SDK_INT >= 36 && !openBed)
            {
                VibrationEffect effect = (VibrationEffect) envelope(
                        "build",
                        new Class[] {Vibrator.class, long[].class, int[].class, float[].class},
                        vibrator,
                        durations,
                        amplitudes,
                        values);
                if (effect != null)
                {
                    route("envelope");
                    play(effect);
                    return OK;
                }
            }
            if (kind == 0 && he != null && !standardActive)
            {
                long batchStart = SystemClock.elapsedRealtime();
                boolean allowV2 = v2Enabled();
                Object next = !heFailed && hePermitted(1)
                        ? prepareHe(durations, amplitudes, values, 0, allowV2) : null;
                if (next != null)
                {
                    if (he.stop())
                    {
                        // Cancellation can occupy part of the new batch. Only submit its live suffix.
                        requirePermit();
                        next = prepareHe(durations, amplitudes, values, SystemClock.elapsedRealtime() - batchStart, allowV2);
                        if (next == null)
                            return SILENT;
                    }
                    requirePermit();
                    if (!hePermitted(allowV2 ? 2 : 1)) return SILENT;
                    delivered = true;
                    he.start(next);
                    route("HE");
                    return OK;
                }
                if (he.playing())
                {
                    // The previous batch may still be audible. End it and decline this replacement.
                    he.stop();
                    return SILENT;
                }
            }
            if (kind == 0)
                route(Build.VERSION.SDK_INT >= 26 && vibrator.hasAmplitudeControl() ? "amplitude" : "binary");
            if (kind == 1)
            {
                if (Build.VERSION.SDK_INT >= 26)
                    play(VibrationEffect.createOneShot(durations[0], amplitudes[0]));
                else
                {
                    requirePermit();
                    delivered = true;
                    vibrator.vibrate(durations[0], GAME);
                }
            }
            else if (Build.VERSION.SDK_INT >= 26 && vibrator.hasAmplitudeControl())
            {
                play(VibrationEffect.createWaveform(durations, amplitudes, -1));
            }
            else
            {
                long[] pattern;
                if (kind == 0)
                    pattern = binary(durations, amplitudes);
                else
                {
                    long[] steps = new long[129];
                    int slot     = 0;
                    for (int i = 0; i < durations.length; i++)
                    {
                        if ((amplitudes[i] != 0) != ((slot & 1) != 0))
                            slot++;
                        if (slot >= 128)
                            return INVALID;
                        steps[slot] += durations[i];
                    }
                    pattern = Arrays.copyOf(steps, slot + 1);
                }
                if (pattern == null)
                    return SILENT;
                if (Build.VERSION.SDK_INT >= 26)
                    play(VibrationEffect.createWaveform(pattern, -1));
                else
                {
                    requirePermit();
                    delivered = true;
                    vibrator.vibrate(pattern, -1, GAME);
                }
            }
            return OK;
        }
        catch (ReflectiveOperationException | LinkageError unknown)
        {
            // Later requests use the public route once the pending handle has stopped.
            heFailed = true;
            try
            {
                if (he != null) he.stop();
            }
            catch (ReflectiveOperationException | RuntimeException | LinkageError stopFailed)
            {
                android.util.Log.w("CocosHaptics", "HE stop pending", stopFailed);
            }
            android.util.Log.w("CocosHaptics", "HE delivery unknown", unknown);
            return FAILED;
        }
        catch (java.util.concurrent.CancellationException e)
        {
            return BUSY;
        }
        catch (SecurityException e)
        {
            return DENIED;
        }
        catch (IllegalArgumentException | IllegalStateException e)
        {
            return INVALID;
        }
        catch (RuntimeException e)
        {
            return FAILED;
        }
    }
    private boolean v2Enabled()
    {
        return heV2Allowed && context.getSharedPreferences("cocos_haptics", Context.MODE_PRIVATE)
                .getBoolean("he_v2_enabled", true);
    }

    private boolean hePermitted(int version)
    {
        return context.getSharedPreferences("cocos_haptics", Context.MODE_PRIVATE).getBoolean("he_enabled", false)
                && (version == 1 || v2Enabled()) && permitsHe(context) && active && nativePermitted();
    }

    // Construction is reversible. Once start is invoked, keep this exact handle
    // until the same serialized stop path runs, including on ambiguous failure.
    int executeOriginal(byte[] bytes, int version)
    {
        if (he == null || heFailed || standardActive || he.playing() || (version != 1 && version != 2)
                || !hePermitted(version))
            return ORIGINAL_DECLINED;
        Object player;
        try
        {
            String json = new String(bytes, java.nio.charset.StandardCharsets.UTF_8);
            player = he.prepare(json);
        }
        catch (ReflectiveOperationException | RuntimeException | LinkageError unavailable)
        {
            return ORIGINAL_DECLINED;
        }
        if (player == null || !hePermitted(version))
            return ORIGINAL_DECLINED;
        try
        {
            delivered = true;
            he.start(player);
            route("HE author v" + version);
            return OK;
        }
        catch (ReflectiveOperationException | RuntimeException | LinkageError unknown)
        {
            heFailed = true;
            return FAILED;
        }
    }
    private Object prepareHe(long[] times, int[] amplitudes, float[] texture, long elapsed, boolean allowV2)
    {
        if (elapsed > 0)
        {
            int first = 0;
            while (first < times.length && elapsed >= times[first])
                elapsed -= times[first++];
            if (first == times.length)
                return null;
            times = Arrays.copyOfRange(times, first, times.length);
            times[0] -= elapsed;
            amplitudes = Arrays.copyOfRange(amplitudes, first, amplitudes.length);
            texture = Arrays.copyOfRange(texture, first, texture.length);
        }
        String json = CocosHapticsHe.encode(times, amplitudes, texture, allowV2);
        if (json == null)
            return null;
        try
        {
            return he.prepare(json);
        }
        catch (ReflectiveOperationException | RuntimeException | LinkageError unavailable)
        {
            route("HE construction failed");
            return null;
        }
    }

    int stop()
    {
        try
        {
            if (!delivered)
                return OK;
            if (he != null && he.playing())
            {
                he.stop();
                route("HE stopped");
            }
            else
                vibrator.cancel();
            standardActive = false;
            if (stopBoundMs == 0)
                return UNSUPPORTED;
            SystemClock.sleep(stopBoundMs);
            delivered = false;
            return OK;
        }
        catch (ReflectiveOperationException | LinkageError e)
        {
            heFailed = true;
            return FAILED;
        }
        catch (SecurityException e)
        {
            return DENIED;
        }
        catch (RuntimeException e)
        {
            return FAILED;
        }
    }
}
