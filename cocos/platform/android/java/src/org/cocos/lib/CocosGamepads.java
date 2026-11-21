package org.cocos.lib;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.hardware.input.InputManager;
import android.hardware.lights.Light;
import android.hardware.lights.LightState;
import android.hardware.lights.LightsManager;
import android.hardware.lights.LightsRequest;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.util.SparseArray;
import android.util.SparseBooleanArray;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.concurrent.atomic.AtomicLong;

/** UI-thread collection of game controller input, shared by application and templates. */
final class CocosGamepads implements InputManager.InputDeviceListener {
    private static final AtomicLong next = new AtomicLong();
    private static volatile CocosGamepads current;
    // These indices are the Android indices used in the SDL mapping database.
    private static final int[][] BUTTONS = {
        {KeyEvent.KEYCODE_BUTTON_A, KeyEvent.KEYCODE_DPAD_CENTER}, {KeyEvent.KEYCODE_BUTTON_B},
        {KeyEvent.KEYCODE_BUTTON_X}, {KeyEvent.KEYCODE_BUTTON_Y},
        {KeyEvent.KEYCODE_BUTTON_SELECT, KeyEvent.KEYCODE_BACK}, {KeyEvent.KEYCODE_BUTTON_MODE},
        {KeyEvent.KEYCODE_BUTTON_START, KeyEvent.KEYCODE_MENU},
        {KeyEvent.KEYCODE_BUTTON_THUMBL}, {KeyEvent.KEYCODE_BUTTON_THUMBR}, {KeyEvent.KEYCODE_BUTTON_L1},
        {KeyEvent.KEYCODE_BUTTON_R1}, {KeyEvent.KEYCODE_DPAD_UP}, {KeyEvent.KEYCODE_DPAD_DOWN},
        {KeyEvent.KEYCODE_DPAD_LEFT}, {KeyEvent.KEYCODE_DPAD_RIGHT}, {KeyEvent.KEYCODE_BUTTON_L2},
        {KeyEvent.KEYCODE_BUTTON_R2}, {KeyEvent.KEYCODE_BUTTON_C}, {KeyEvent.KEYCODE_BUTTON_Z}, {},
        {KeyEvent.KEYCODE_BUTTON_1}, {KeyEvent.KEYCODE_BUTTON_2}, {KeyEvent.KEYCODE_BUTTON_3}, {KeyEvent.KEYCODE_BUTTON_4},
        {KeyEvent.KEYCODE_BUTTON_5}, {KeyEvent.KEYCODE_BUTTON_6}, {KeyEvent.KEYCODE_BUTTON_7}, {KeyEvent.KEYCODE_BUTTON_8},
        {KeyEvent.KEYCODE_BUTTON_9}, {KeyEvent.KEYCODE_BUTTON_10}, {KeyEvent.KEYCODE_BUTTON_11}, {KeyEvent.KEYCODE_BUTTON_12},
        {KeyEvent.KEYCODE_BUTTON_13}, {KeyEvent.KEYCODE_BUTTON_14}, {KeyEvent.KEYCODE_BUTTON_15}, {KeyEvent.KEYCODE_BUTTON_16}
    };
    private static final int[][] AXES = {
        {MotionEvent.AXIS_X}, {MotionEvent.AXIS_Y}, {MotionEvent.AXIS_Z, MotionEvent.AXIS_RX},
        {MotionEvent.AXIS_RZ, MotionEvent.AXIS_RY}, {MotionEvent.AXIS_LTRIGGER, MotionEvent.AXIS_BRAKE},
        {MotionEvent.AXIS_RTRIGGER, MotionEvent.AXIS_GAS}
    };

    private static int axisOrder(int axis) {
        if (axis == MotionEvent.AXIS_GAS) return MotionEvent.AXIS_BRAKE;
        if (axis == MotionEvent.AXIS_BRAKE) return MotionEvent.AXIS_GAS;
        if (axis == MotionEvent.AXIS_Z) return MotionEvent.AXIS_RZ - 1;
        return axis > MotionEvent.AXIS_Z && axis < MotionEvent.AXIS_RZ ? axis - 1 : axis;
    }

    private static final class Pad {
        final long generation = next.incrementAndGet();
        final ArrayList<InputDevice.MotionRange> ranges = new ArrayList<>();
        final int[] defaultAxes = new int[AXES.length];
        final SparseBooleanArray keyState = new SparseBooleanArray();
        InputDevice.MotionRange hatX, hatY;
        final Vibrator vibrator;
        final long buttons;
        final int axisMask;
        final String axisLayout;
        final DeviceExtras extras;

        Pad(InputDevice device) {
            HashSet<Integer> seen = new HashSet<>();
            for (InputDevice.MotionRange range : device.getMotionRanges()) {
                int axis = range.getAxis();
                if ((range.getSource() & InputDevice.SOURCE_CLASS_JOYSTICK) == 0 || !seen.add(axis)) continue;
                if (axis == MotionEvent.AXIS_HAT_X) hatX = range;
                else if (axis == MotionEvent.AXIS_HAT_Y) hatY = range;
                else ranges.add(range);
            }
            ranges.sort((first, second) -> Integer.compare(axisOrder(first.getAxis()), axisOrder(second.getAxis())));
            StringBuilder axisIds = new StringBuilder();
            for (InputDevice.MotionRange range : ranges) axisIds.append('/').append(range.getAxis());
            axisLayout = axisIds.toString();
            int mask = ranges.size() >= 6 ? 0x3f : ranges.size() >= 4 ? 0x0f : ranges.size() >= 2 ? 0x03 : 0;
            if (seen.contains(MotionEvent.AXIS_Z) && (seen.contains(MotionEvent.AXIS_RX) || seen.contains(MotionEvent.AXIS_RY)))
                mask |= 0x8000;
            axisMask = mask;
            for (int output = 0; output < AXES.length; ++output) {
                defaultAxes[output] = -1;
                for (int axis : AXES[output]) {
                    for (int input = 0; input < ranges.size(); ++input) {
                        InputDevice.MotionRange range = ranges.get(input);
                        if (range.getAxis() == axis && range.getMax() > range.getMin()) {
                            defaultAxes[output] = input;
                            break;
                        }
                    }
                    if (defaultAxes[output] >= 0) break;
                }
            }
            long buttonMask = 0;
            for (int i = 0; i < BUTTONS.length; ++i) {
                if (BUTTONS[i].length == 0) continue;
                for (boolean supported : device.hasKeys(BUTTONS[i])) if (supported) buttonMask |= 1L << i;
            }
            if (hatX != null) buttonMask |= (1 << 13) | (1 << 14);
            if (hatY != null) buttonMask |= (1 << 11) | (1 << 12);
            buttons = buttonMask;
            Vibrator v = Build.VERSION.SDK_INT >= 31
                ? device.getVibratorManager().getDefaultVibrator() : device.getVibrator();
            vibrator = v != null && v.hasVibrator() ? v : null;
            extras = Build.VERSION.SDK_INT >= 31 ? new DeviceExtras(device) : null;
        }

        boolean hatOwns(int button) {
            return (button == 11 || button == 12) && hatY != null
                || (button == 13 || button == 14) && hatX != null;
        }

        int layoutMask() {
            return (buttons >>> 32) != 0 ? 0xffff : (int) buttons & 0xffff;
        }

        short value(MotionEvent event, InputDevice.MotionRange range, int history, boolean hat) {
            if (range == null) return 2;
            int axis = range.getAxis();
            float value = history < 0 ? event.getAxisValue(axis) : event.getHistoricalAxisValue(axis, history);
            if (hat) return (short) (value <= -.5f ? -1 : value >= .5f ? 1 : 0);
            if (range.getMax() <= range.getMin()) return 0;
            if (range.getMin() < 0 && range.getMax() > 0) {
                if (Math.abs(value) <= range.getFlat()) return 0;
                float fraction = value < 0 ? value / -range.getMin() : value / range.getMax();
                return (short) Math.round(Math.max(-1f, Math.min(1f, fraction)) * (value < 0 ? 32768 : 32767));
            }
            float fraction = (value - range.getMin()) / (range.getMax() - range.getMin());
            return (short) (Math.round(Math.max(0f, Math.min(1f, fraction)) * 65535) - 32768);
        }
    }

    private static final class DeviceExtras {
        final SensorManager manager;
        final Sensor[] sensors = new Sensor[2];
        final SensorEventListener[] listeners = new SensorEventListener[2];
        final LightsManager lights;
        final Light rgb;
        LightsManager.LightsSession lightSession;
        int requested;

        DeviceExtras(InputDevice device) {
            manager = device.getSensorManager();
            sensors[0] = manager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
            sensors[1] = manager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
            lights = device.getLightsManager();
            Light found = null;
            for (Light light : lights.getLights()) {
                if (light.getType() == Light.LIGHT_TYPE_INPUT && light.hasRgbControl()) {
                    found = light;
                    break;
                }
            }
            rgb = found;
        }

        int capabilities() {
            return (sensors[0] != null ? 1 : 0) | (sensors[1] != null ? 2 : 0) | (rgb != null ? 4 : 0);
        }

        void updateSensors(CocosGamepads collector, int id, Pad pad) {
            for (int i = 0; i < sensors.length; ++i) {
                boolean enable = collector.resumed && collector.engineActive && (requested & (1 << i)) != 0;
                if (!enable && listeners[i] != null) {
                    manager.unregisterListener(listeners[i], sensors[i]);
                    listeners[i] = null;
                } else if (enable && listeners[i] == null && sensors[i] != null) {
                    final int index = i;
                    SensorEventListener listener = new SensorEventListener() {
                        @Override public void onAccuracyChanged(Sensor sensor, int accuracy) {}
                        @Override public void onSensorChanged(SensorEvent event) {
                            if (listeners[index] == this && event.values.length >= 3)
                                nativeSensor(collector.host, id, pad.generation, index, event.timestamp,
                                    event.values[0], event.values[1], event.values[2]);
                        }
                    };
                    if (manager.registerListener(listener, sensors[i], SensorManager.SENSOR_DELAY_GAME, collector.handler))
                        listeners[i] = listener;
                }
            }
        }

        void clearLight() {
            if (lightSession != null) {
                try { lightSession.close(); }
                catch (RuntimeException ignored) {}
                lightSession = null;
            }
        }

        boolean setLight(int color) {
            if (rgb == null) return false;
            if (lightSession == null) lightSession = lights.openSession();
            lightSession.requestLights(new LightsRequest.Builder()
                .addLight(rgb, new LightState.Builder().setColor(color).build()).build());
            return true;
        }
    }

    private final InputManager manager;
    private final Handler handler = new Handler(Looper.getMainLooper());
    private final SparseArray<Pad> devices = new SparseArray<>();
    private final long host = next.incrementAndGet();
    private boolean resumed, engineActive = true;

    CocosGamepads(Context context) {
        manager = (InputManager) context.getSystemService(Context.INPUT_SERVICE);
        current = this;
        nativeHost(host, true);
        manager.registerInputDeviceListener(this, handler);
        for (int id : manager.getInputDeviceIds()) onInputDeviceAdded(id);
    }

    private static boolean gamepad(int source) {
        return (source & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD
            || (source & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK;
    }

    @Override public void onInputDeviceAdded(int id) {
        if (current != this || devices.get(id) != null) return;
        InputDevice device = manager.getInputDevice(id);
        if (device == null || !gamepad(device.getSources())) return;
        Pad pad = new Pad(device);
        if (pad.buttons == 0 && pad.ranges.isEmpty()) return;
        devices.put(id, pad);
        String descriptor = device.getDescriptor();
        if (descriptor == null || descriptor.isEmpty()) descriptor = device.getName();
        nativeAttach(host, id, pad.generation, device.getName(), descriptor, device.getVendorId(), device.getProductId(),
            pad.buttons, pad.layoutMask(), pad.axisMask, pad.axisLayout, pad.ranges.size(), pad.defaultAxes, pad.vibrator != null,
            pad.extras != null ? pad.extras.capabilities() : 0);
    }

    @Override public void onInputDeviceRemoved(int id) {
        Pad pad = devices.get(id);
        if (pad == null) return;
        cancel(pad);
        if (pad.extras != null) {
            pad.extras.requested = 0;
            pad.extras.updateSensors(this, id, pad);
            pad.extras.clearLight();
        }
        nativeDetach(host, id, pad.generation);
        devices.delete(id);
    }

    @Override public void onInputDeviceChanged(int id) {
        onInputDeviceRemoved(id);
        onInputDeviceAdded(id);
    }

    boolean key(KeyEvent event) {
        if (current != this || (!gamepad(event.getSource()) &&
            (event.getSource() & InputDevice.SOURCE_DPAD) != InputDevice.SOURCE_DPAD)) return false;
        Pad pad = devices.get(event.getDeviceId());
        if (pad == null) return false;
        int action = event.getAction();
        if (action != KeyEvent.ACTION_DOWN && action != KeyEvent.ACTION_UP) return false;
        int key = event.getKeyCode();
        for (int index = 0; index < BUTTONS.length; ++index) {
            for (int code : BUTTONS[index]) {
                if (key != code || (pad.buttons & (1L << index)) == 0) continue;
                if (pad.hatOwns(index) || event.getRepeatCount() != 0)
                    return nativeClaimed(host, event.getDeviceId(), pad.generation);
                pad.keyState.put(key, action == KeyEvent.ACTION_DOWN);
                boolean down = false;
                for (int alias : BUTTONS[index]) down |= pad.keyState.get(alias);
                return nativeKey(host, event.getDeviceId(), pad.generation, index, down, event.getEventTime());
            }
        }
        return false;
    }

    boolean motion(MotionEvent event) {
        if (current != this || (event.getSource() & InputDevice.SOURCE_JOYSTICK) != InputDevice.SOURCE_JOYSTICK
            || event.getActionMasked() != MotionEvent.ACTION_MOVE) return false;
        Pad pad = devices.get(event.getDeviceId());
        if (pad == null) return false;
        int history = event.getHistorySize();
        int first = Math.max(0, history - 1023);
        int count = history - first + 1;
        long[] times = new long[count];
        int axes = pad.ranges.size();
        int stride = axes + 2;
        short[] data = new short[count * stride];
        for (int sample = 0; sample < count; ++sample) {
            int position = sample + first;
            boolean latest = position == history;
            times[sample] = latest ? event.getEventTime() : event.getHistoricalEventTime(position);
            int sampleHistory = latest ? -1 : position;
            for (int axis = 0; axis < axes; ++axis)
                data[sample * stride + axis] = pad.value(event, pad.ranges.get(axis), sampleHistory, false);
            data[sample * stride + axes] = pad.value(event, pad.hatX, sampleHistory, true);
            data[sample * stride + axes + 1] = pad.value(event, pad.hatY, sampleHistory, true);
        }
        return nativeMotion(host, event.getDeviceId(), pad.generation, times, data);
    }

    private static void cancel(Pad pad) {
        if (pad.vibrator != null) {
            try { pad.vibrator.cancel(); }
            catch (SecurityException ignored) {}
        }
    }

    void setResumed(boolean value) {
        resumed = value;
        updateLifecycle();
    }

    private void updateLifecycle() {
        for (int i = 0; i < devices.size(); ++i) {
            Pad pad = devices.valueAt(i);
            if (!resumed || !engineActive) {
                pad.keyState.clear();
                cancel(pad);
            }
            if (pad.extras != null) {
                pad.extras.updateSensors(this, devices.keyAt(i), pad);
                if (!resumed || !engineActive) pad.extras.clearLight();
            }
        }
    }

    void close() {
        setResumed(false);
        manager.unregisterInputDeviceListener(this);
        if (current == this) current = null;
        nativeHost(host, false);
        devices.clear();
    }

    static boolean setActive(long host, boolean active) {
        CocosGamepads collector = current;
        return collector != null && collector.host == host && collector.handler.post(() -> {
            if (collector != current) return;
            collector.engineActive = active;
            collector.updateLifecycle();
        });
    }

    static boolean setSensor(long host, int id, long endpoint, int index, boolean enabled) {
        CocosGamepads collector = current;
        return collector != null && collector.host == host && collector.handler.post(() -> {
            Pad pad = collector.devices.get(id);
            if (collector != current || pad == null || pad.generation != endpoint || pad.extras == null) return;
            if (enabled) pad.extras.requested |= 1 << index;
            else pad.extras.requested &= ~(1 << index);
            pad.extras.updateSensors(collector, id, pad);
        });
    }

    static boolean queueOutput(long host, int id, long endpoint, long generation, long command,
                               int operation, int value, float amount) {
        CocosGamepads collector = current;
        return collector != null && collector.host == host && collector.handler.post(() -> {
            Pad pad = collector.devices.get(id);
            if (collector != current || pad == null || pad.generation != endpoint) return;
            int result = 0;
            try {
                if (operation == 2 || operation == 3) {
                    if (pad.extras != null) pad.extras.clearLight();
                    if (operation == 3) cancel(pad);
                } else if (operation == 0 && (value <= 0 || amount <= 0f)) cancel(pad);
                else if (!collector.resumed || !collector.engineActive) result = 1;
                else if (operation == 1) {
                    if (pad.extras == null || !pad.extras.setLight(value)) result = 3;
                } else if (pad.vibrator != null) {
                    if (Build.VERSION.SDK_INT >= 26) {
                        int amplitude = pad.vibrator.hasAmplitudeControl() ? Math.max(1, Math.round(amount * 255))
                            : VibrationEffect.DEFAULT_AMPLITUDE;
                        pad.vibrator.vibrate(VibrationEffect.createOneShot(value, amplitude));
                    } else pad.vibrator.vibrate(value);
                } else result = 3;
            } catch (SecurityException failure) { result = 2; }
            catch (RuntimeException failure) { result = 3; }
            nativeOutputDone(host, id, endpoint, generation, command, result);
        });
    }

    private static native void nativeHost(long host, boolean start);
    private static native void nativeAttach(long host, int id, long generation, String name, String descriptor,
                                            int vendor, int product, long buttons, int guidButtons, int guidAxes,
                                            String axisLayout, int axisCount, int[] defaultAxes, boolean feedback, int additional);
    private static native void nativeDetach(long host, int id, long generation);
    private static native boolean nativeClaimed(long host, int id, long generation);
    private static native boolean nativeKey(long host, int id, long generation, int index, boolean down, long timestamp);
    private static native boolean nativeMotion(long host, int id, long generation, long[] times, short[] values);
    private static native void nativeSensor(long host, int id, long generation, int index, long timestamp,
                                            float x, float y, float z);
    private static native void nativeOutputDone(long host, int id, long endpoint, long generation, long command, int status);
}
