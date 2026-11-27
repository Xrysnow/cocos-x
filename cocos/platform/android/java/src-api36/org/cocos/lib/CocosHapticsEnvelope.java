package org.cocos.lib;

import android.annotation.TargetApi;
import android.os.Build;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.os.vibrator.VibratorEnvelopeEffectInfo;
import android.os.vibrator.VibratorFrequencyProfile;

@TargetApi(36)
public final class CocosHapticsEnvelope {
    private static final int MAX_POINTS = 64;
    private static final int MAX_BATCH_MS = 1000;

    private CocosHapticsEnvelope() {}

    private static VibratorEnvelopeEffectInfo deviceLimits(Vibrator vibrator) {
        if (Build.VERSION.SDK_INT < 36 || vibrator == null || !vibrator.areEnvelopeEffectsSupported()) {
            return null;
        }
        return vibrator.getEnvelopeEffectInfo();
    }

    public static long[] limits(Vibrator vibrator) {
        VibratorEnvelopeEffectInfo limits = deviceLimits(vibrator);
        if (limits == null || limits.getMaxSize() < 2 || limits.getMinControlPointDurationMillis() <= 0
                || limits.getMaxControlPointDurationMillis() < limits.getMinControlPointDurationMillis()
                || limits.getMaxDurationMillis() < limits.getMinControlPointDurationMillis()) {
            return null;
        }
        return new long[]{Math.min(limits.getMaxSize(), MAX_POINTS), limits.getMinControlPointDurationMillis(),
                limits.getMaxControlPointDurationMillis(), Math.min(limits.getMaxDurationMillis(), MAX_BATCH_MS)};
    }

    public static float[] frequencyRange(Vibrator vibrator) {
        if (Build.VERSION.SDK_INT < 36 || vibrator == null) {
            return null;
        }
        VibratorFrequencyProfile profile = vibrator.getFrequencyProfile();
        if (profile == null) {
            return null;
        }
        float min = profile.getMinFrequencyHz();
        float max = profile.getMaxFrequencyHz();
        return Float.isFinite(min) && Float.isFinite(max) && min > 0 && min <= max
                ? new float[]{min, max} : null;
    }

    public static VibrationEffect build(Vibrator vibrator, long[] durations, int[] amplitudes, float[] textures) {
        long[] limits = limits(vibrator);
        if (limits == null || durations == null || amplitudes == null || textures == null || durations.length == 0
                || durations.length != amplitudes.length || durations.length != textures.length) {
            return null;
        }
        long total = 0;
        boolean audible = false;
        for (int index = 0; index < durations.length; ++index) {
            if (durations[index] <= 0 || durations[index] > limits[3] - total
                    || amplitudes[index] < 0 || amplitudes[index] > 255 || !Float.isFinite(textures[index])
                    || textures[index] < 0 || textures[index] > 1) {
                return null;
            }
            total += durations[index];
            audible |= amplitudes[index] != 0;
        }
        if (!audible) {
            return null;
        }

        // Place each ramp on the louder side of its boundary so it never fills a silent interval
        // or raises the requested drive within a quieter interval.
        BasicPlan plan = new BasicPlan((int) limits[0], limits[1], limits[2], textures[0]);
        int previous = 0;
        for (int index = 0; index < durations.length;) {
            int current = amplitudes[index];
            float texture = textures[index];
            long duration = 0;
            do {
                duration += durations[index++];
            } while (index < durations.length && amplitudes[index] == current && textures[index] == texture);
            int next = index < durations.length ? amplitudes[index] : 0;
            if (current > previous) {
                duration -= plan.minDuration;
                if (!plan.point(current, texture, plan.minDuration)) {
                    return null;
                }
            }
            if (next < current) {
                duration -= plan.minDuration;
            }
            float nextTexture = index < textures.length ? textures[index] : texture;
            if (!plan.hold(current, texture, duration) || (next < current && !plan.point(next, nextTexture, plan.minDuration))) {
                return null;
            }
            previous = current;
        }
        return plan.builder.build();
    }

    public static VibrationEffect raw(Vibrator vibrator, boolean frequency, long[] durations,
                                      float[] intensities, float[] textures) {
        long[] limits = limits(vibrator);
        if (limits == null || durations == null || intensities == null || textures == null
                || durations.length < 2 || durations.length > limits[0]
                || durations.length != intensities.length || durations.length != textures.length
                || intensities[intensities.length - 1] != 0.0f) {
            return null;
        }
        float[] textureRange = frequency ? frequencyRange(vibrator) : new float[]{0.0f, 1.0f};
        if (textureRange == null) {
            return null;
        }
        long total = 0;
        boolean audible = false;
        for (int index = 0; index < durations.length; ++index) {
            if (durations[index] < limits[1] || durations[index] > limits[2] || durations[index] > limits[3] - total
                    || !Float.isFinite(intensities[index]) || intensities[index] < 0 || intensities[index] > 1
                    || !Float.isFinite(textures[index]) || textures[index] < textureRange[0]
                    || textures[index] > textureRange[1]) {
                return null;
            }
            total += durations[index];
            audible |= intensities[index] > 0;
        }
        if (!audible) {
            return null;
        }

        if (frequency) {
            VibrationEffect.WaveformEnvelopeBuilder builder = new VibrationEffect.WaveformEnvelopeBuilder()
                    .setInitialFrequencyHz(textures[0]);
            for (int index = 0; index < durations.length; ++index) {
                builder.addControlPoint(intensities[index], textures[index], durations[index]);
            }
            return builder.build();
        }
        VibrationEffect.BasicEnvelopeBuilder builder = new VibrationEffect.BasicEnvelopeBuilder()
                .setInitialSharpness(textures[0]);
        for (int index = 0; index < durations.length; ++index) {
            builder.addControlPoint(intensities[index], textures[index], durations[index]);
        }
        return builder.build();
    }

    private static final class BasicPlan {
        final VibrationEffect.BasicEnvelopeBuilder builder;
        final long minDuration;
        private final long maxDuration;
        private int pointsLeft;

        BasicPlan(int maxPoints, long minDuration, long maxDuration, float firstTexture) {
            builder = new VibrationEffect.BasicEnvelopeBuilder().setInitialSharpness(firstTexture);
            pointsLeft = maxPoints;
            this.minDuration = minDuration;
            this.maxDuration = maxDuration;
        }

        boolean point(int amplitude, float texture, long duration) {
            if (pointsLeft == 0 || duration < minDuration || duration > maxDuration) {
                return false;
            }
            builder.addControlPoint(amplitude / 255.0f, texture, duration);
            --pointsLeft;
            return true;
        }

        boolean hold(int amplitude, float texture, long duration) {
            if (duration == 0) {
                return true;
            }
            if (duration < minDuration) {
                return false;
            }
            long pieces = 1 + (duration - 1) / maxDuration;
            long pieceDuration = duration / pieces;
            long remainder = duration % pieces;
            for (long piece = 0; piece < pieces; ++piece) {
                if (!point(amplitude, texture, pieceDuration + (piece < remainder ? 1 : 0))) {
                    return false;
                }
            }
            return true;
        }
    }
}
