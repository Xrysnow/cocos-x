package org.cocos.lib;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
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
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.util.SparseArray;
import android.util.SparseBooleanArray;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.concurrent.atomic.AtomicLong;

/** UI-thread collection of game controller input, shared by application and templates. */
final class CocosGamepads implements InputManager.InputDeviceListener {
    private static final AtomicLong next = new AtomicLong();
    static long nextEndpoint() { return next.incrementAndGet(); }
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
        final long generation = nextEndpoint();
        final String descriptor;
        final boolean touchpad;
        final int touchpadMaxY;
        int sources;
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
            descriptor = device.getDescriptor();
            sources = device.getSources();
            touchpad = Build.VERSION.SDK_INT >= 26
                && CocosSonyGamepadUsb.supports(device.getVendorId(), device.getProductId())
                && (device.supportsSource(InputDevice.SOURCE_MOUSE) || device.supportsSource(InputDevice.SOURCE_TOUCHPAD));
            touchpadMaxY = CocosSonyGamepadUsb.isDualShock4(device.getProductId()) ? 943 : 1079;
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
        final boolean remoteSensors;
        final Sensor[] sensors = new Sensor[2];
        final SensorEventListener[] listeners = new SensorEventListener[2];
        final LightsManager lights;
        final Light rgb;
        LightsManager.LightsSession lightSession;
        int requested;

        DeviceExtras(InputDevice device) {
            boolean hasSensors = device.supportsSource(InputDevice.SOURCE_SENSOR);
            remoteSensors = hasSensors && Build.VERSION.SDK_INT < 33;
            manager = hasSensors && !remoteSensors ? device.getSensorManager() : null;
            if (manager != null) {
                sensors[0] = manager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
                sensors[1] = manager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
            }
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
            if (remoteSensors) {
                collector.sensorClient.update(id, pad);
                return;
            }
            if (manager == null) return;
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

    private final class SensorClient implements ServiceConnection {
        final Context context;
        final Messenger replies = new Messenger(new Handler(Looper.getMainLooper(), this::receive));
        Messenger service;
        boolean bound;

        SensorClient(Context context) { this.context = context.getApplicationContext(); }

        void update(int id, Pad pad) {
            if (!bound && resumed) {
                bound = context.bindService(new Intent(context, CocosGamepadSensorService.class),
                    this, Context.BIND_AUTO_CREATE);
            }
            send(CocosGamepadSensorService.UPDATE, id, pad.generation,
                resumed && engineActive ? pad.extras.requested : 0);
        }

        void remove(int id, Pad pad) {
            send(CocosGamepadSensorService.REMOVE, id, pad.generation, 0);
        }

        private void send(int what, int id, long endpoint, int request) {
            if (service == null) return;
            Message message = Message.obtain(null, what, id, request);
            message.replyTo = replies;
            message.getData().putLong(CocosGamepadSensorService.ENDPOINT, endpoint);
            try { service.send(message); }
            catch (RemoteException ignored) { service = null; }
        }

        private boolean receive(Message message) {
            Pad pad = devices.get(message.arg1);
            if (current != CocosGamepads.this || pad == null || pad.extras == null || !pad.extras.remoteSensors
                || pad.generation != message.getData().getLong(CocosGamepadSensorService.ENDPOINT)) return true;
            if (message.what == CocosGamepadSensorService.CAPABILITIES) {
                nativeSensorCapabilities(host, message.arg1, pad.generation, message.arg2);
            } else if (message.what == CocosGamepadSensorService.SAMPLE && message.arg2 >= 0 && message.arg2 < 2
                && resumed && engineActive && (pad.extras.requested & (1 << message.arg2)) != 0) {
                float[] values = message.getData().getFloatArray(CocosGamepadSensorService.VALUES);
                if (values != null && values.length == 3)
                    nativeSensor(host, message.arg1, pad.generation, message.arg2,
                        message.getData().getLong(CocosGamepadSensorService.TIMESTAMP), values[0], values[1], values[2]);
            }
            return true;
        }

        @Override public void onServiceConnected(ComponentName name, IBinder binder) {
            if (!bound || current != CocosGamepads.this) return;
            service = new Messenger(binder);
            sync();
        }

        @Override public void onServiceDisconnected(ComponentName name) { service = null; }

        @Override public void onBindingDied(ComponentName name) {
            close();
            handler.postDelayed(() -> {
                if (current == CocosGamepads.this && resumed) sync();
            }, 250);
        }

        private void sync() {
            for (int i = 0; i < devices.size(); ++i) {
                Pad pad = devices.valueAt(i);
                if (pad.extras != null && pad.extras.remoteSensors) update(devices.keyAt(i), pad);
            }
        }

        void close() {
            if (bound) context.unbindService(this);
            bound = false;
            service = null;
        }
    }

    private final InputManager manager;
    private final SensorClient sensorClient;
    private final CocosSonyGamepadUsb usb;
    private final Handler handler = new Handler(Looper.getMainLooper());
    private final SparseArray<Pad> devices = new SparseArray<>();
    private final long host = next.incrementAndGet();
    private boolean resumed, engineActive = true;
    private View captureView;
    private boolean captureRequested, absoluteCaptureAvailable = true;

    CocosGamepads(Context context) {
        manager = (InputManager) context.getSystemService(Context.INPUT_SERVICE);
        sensorClient = Build.VERSION.SDK_INT >= 31 && Build.VERSION.SDK_INT < 33 ? new SensorClient(context) : null;
        usb = new CocosSonyGamepadUsb(context, handler, host);
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
            (pad.extras != null ? pad.extras.capabilities() : 0) | (pad.touchpad ? 8 : 0));
        if (pad.extras != null && pad.extras.remoteSensors) sensorClient.update(id, pad);
        updateCapture();
    }

    @Override public void onInputDeviceRemoved(int id) {
        Pad pad = devices.get(id);
        if (pad == null) return;
        cancel(pad);
        if (pad.extras != null) {
            pad.extras.requested = 0;
            if (pad.extras.remoteSensors) sensorClient.remove(id, pad);
            else pad.extras.updateSensors(this, id, pad);
            pad.extras.clearLight();
        }
        nativeDetach(host, id, pad.generation);
        devices.delete(id);
        updateCapture();
    }

    @Override public void onInputDeviceChanged(int id) {
        Pad pad = devices.get(id);
        InputDevice device = manager.getInputDevice(id);
        if (pad != null && pad.touchpad && device != null && pad.descriptor != null
            && pad.descriptor.equals(device.getDescriptor())) {
            int changed = pad.sources ^ device.getSources();
            int pointerSources = InputDevice.SOURCE_TOUCHPAD | InputDevice.SOURCE_MOUSE;
            // Pointer capture makes Android reconfigure the touchpad source on the same logical device.
            if (changed != 0 && (changed & ~pointerSources) == 0) {
                pad.sources = device.getSources();
                return;
            }
        }
        onInputDeviceRemoved(id);
        onInputDeviceAdded(id);
    }

    void bindCaptureView(View view) {
        if (Build.VERSION.SDK_INT < 26) return;
        captureView = view;
        view.setOnCapturedPointerListener((ignored, event) -> touchpad(event));
        updateCapture();
    }

    void updateCapture() {
        if (Build.VERSION.SDK_INT < 26 || captureView == null) return;
        boolean want = false;
        if (resumed && engineActive && absoluteCaptureAvailable && captureView.hasWindowFocus()) {
            for (int i = 0; i < devices.size() && !want; ++i) want = devices.valueAt(i).touchpad;
        }
        if (want == captureRequested) return;
        captureRequested = want;
        if (want) {
            if (Build.VERSION.SDK_INT < 37) captureView.requestPointerCapture();
            else {
                // The public absolute overload is newer than this library's compile SDK.
                try {
                    int mode = View.class.getField("POINTER_CAPTURE_MODE_ABSOLUTE").getInt(null);
                    View.class.getMethod("requestPointerCapture", int.class).invoke(captureView, mode);
                } catch (ReflectiveOperationException failure) {
                    absoluteCaptureAvailable = false;
                    captureRequested = false;
                    Log.w("CocosGamepads", "Absolute gamepad touchpad capture is unavailable", failure);
                }
            }
        } else {
            captureView.releasePointerCapture();
            for (int i = 0; i < devices.size(); ++i) {
                Pad pad = devices.valueAt(i);
                if (pad.touchpad) nativeTouch(host, devices.keyAt(i), pad.generation, -1, 0, 0, -1, 0, 0, true, 0);
            }
        }
    }

    boolean touchpad(MotionEvent event) {
        if (current != this || !captureRequested || event.getSource() != InputDevice.SOURCE_TOUCHPAD) return false;
        int id = event.getDeviceId();
        Pad pad = devices.get(id);
        if (pad == null || !pad.touchpad) return false;
        int action = event.getActionMasked();
        if (action == MotionEvent.ACTION_CANCEL || action == MotionEvent.ACTION_UP) {
            nativeTouch(host, id, pad.generation, -1, 0, 0, -1, 0, 0,
                action == MotionEvent.ACTION_CANCEL, event.getEventTime());
            return true;
        }
        if (action != MotionEvent.ACTION_DOWN && action != MotionEvent.ACTION_POINTER_DOWN
            && action != MotionEvent.ACTION_MOVE && action != MotionEvent.ACTION_POINTER_UP) return true;
        int first = -1, second = -1;
        for (int i = 0; i < event.getPointerCount(); ++i) {
            if (action == MotionEvent.ACTION_POINTER_UP && i == event.getActionIndex()) continue;
            if (first < 0) first = i;
            else { second = i; break; }
        }
        InputDevice device = event.getDevice();
        InputDevice.MotionRange x = device == null ? null : device.getMotionRange(MotionEvent.AXIS_X, InputDevice.SOURCE_TOUCHPAD);
        InputDevice.MotionRange y = device == null ? null : device.getMotionRange(MotionEvent.AXIS_Y, InputDevice.SOURCE_TOUCHPAD);
        nativeTouch(host, id, pad.generation,
            first < 0 ? -1 : event.getPointerId(first),
            first < 0 ? 0 : normalizeTouch(event.getX(first), x, 1919),
            first < 0 ? 0 : normalizeTouch(event.getY(first), y, pad.touchpadMaxY),
            second < 0 ? -1 : event.getPointerId(second),
            second < 0 ? 0 : normalizeTouch(event.getX(second), x, 1919),
            second < 0 ? 0 : normalizeTouch(event.getY(second), y, pad.touchpadMaxY), false, event.getEventTime());
        return true;
    }

    private static float normalizeTouch(float coordinate, InputDevice.MotionRange range, float fallback) {
        float min = range == null ? 0 : range.getMin();
        float span = range == null ? fallback : range.getRange();
        return Math.max(0f, Math.min(1f, (coordinate - min) / (span > 0 ? span : fallback)));
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
        usb.setResumed(value);
        updateLifecycle();
    }

    private void updateLifecycle() {
        updateCapture();
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
        usb.close();
        manager.unregisterInputDeviceListener(this);
        if (sensorClient != null) sensorClient.close();
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
    private static native void nativeSensorCapabilities(long host, int id, long generation, int mask);
    private static native void nativeTouch(long host, int id, long generation,
        int first, float firstX, float firstY, int second, float secondX, float secondY, boolean cancelled, long timestamp);
    private static native void nativeOutputDone(long host, int id, long endpoint, long generation, long command, int status);
}
