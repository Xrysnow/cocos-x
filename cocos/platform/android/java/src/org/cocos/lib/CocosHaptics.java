package org.cocos.lib;

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
                             SILENT        = 256;
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
    private boolean delivered;
    private final ArrayDeque<Long> binaryOn = new ArrayDeque<>();
    private long nextBinaryOn;
    private CocosHaptics(Vibrator v, int id, String name)
    {
        vibrator    = v;
        deviceId    = id;
        descriptor  = name;
        stopBoundMs = verifiedStopBound(id == HANDSET ? "handset" : name);
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
                | (deviceId == HANDSET && forwarding() ? 4 : 0) | (stopBoundMs > 0 ? 8 : 0);
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
        boolean[] on  = new boolean[size];
        long origin   = SystemClock.elapsedRealtime();
        int cursor    = 0;
        double credit = 0;
        boolean above = false;
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
                credit   = Math.min(24, credit + level * level);
                long now = origin + cursor;
                while (!binaryOn.isEmpty() && binaryOn.peekFirst() <= now - 250) binaryOn.removeFirst();
                if (credit >= 12 && now >= nextBinaryOn && durations[i] - j >= 12 && binaryOn.size() + 12 <= 80)
                {
                    for (int k = 0; k < 12; k++)
                    {
                        on[cursor + k] = true;
                        binaryOn.addLast(now + k);
                    }
                    credit       -= 12;
                    nextBinaryOn  = now + 28;
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
        if (Build.VERSION.SDK_INT >= 33)
            vibrator.vibrate(effect, VibrationAttributes.createForUsage(VibrationAttributes.USAGE_MEDIA));
        else
            vibrator.vibrate(effect, GAME);
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
            if (kind == 0 && BuildConfig.HAPTICS_ENVELOPE_BUILT && Build.VERSION.SDK_INT >= 36 && !openBed)
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
                    play(effect);
                    return OK;
                }
            }
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
    int stop()
    {
        try
        {
            if (!delivered)
                return OK;
            vibrator.cancel();
            if (stopBoundMs == 0)
                return UNSUPPORTED;
            SystemClock.sleep(stopBoundMs);
            delivered = false;
            return OK;
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
