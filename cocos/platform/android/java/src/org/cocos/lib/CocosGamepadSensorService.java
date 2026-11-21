package org.cocos.lib;

import android.app.Service;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.os.Messenger;
import android.os.Process;
import android.os.RemoteException;
import android.util.Log;
import android.util.SparseArray;
import android.view.InputDevice;

/** Keeps the Android 12 input-device sensor manager out of the game process. */
public final class CocosGamepadSensorService extends Service {
    static final int UPDATE = 1, REMOVE = 2, CAPABILITIES = 3, SAMPLE = 4;
    static final String ENDPOINT = "endpoint", TIMESTAMP = "timestamp", VALUES = "values";
    static final int[] TYPES = {Sensor.TYPE_ACCELEROMETER, Sensor.TYPE_GYROSCOPE};
    private final SparseArray<Route> routes = new SparseArray<>();
    private final Handler handler = new Handler(Looper.getMainLooper(), this::receive);
    private final Messenger messenger = new Messenger(handler);

    @Override public void onCreate() {
        super.onCreate();
        Thread.UncaughtExceptionHandler previous = Thread.getDefaultUncaughtExceptionHandler();
        Thread.setDefaultUncaughtExceptionHandler((thread, failure) -> {
            // Android 12 can deliver an add/change for a device that has already vanished.
            // Restart this process to get a fresh framework listener and sensor inventory.
            if (failure instanceof NullPointerException) {
                for (StackTraceElement frame : failure.getStackTrace()) {
                    if (frame.getClassName().equals("android.hardware.input.InputDeviceSensorManager")
                            && frame.getMethodName().equals("updateInputDeviceSensorInfoLocked")) {
                        Log.w("CocosGamepads", "Restarting Android 12 gamepad sensor process", failure);
                        Process.killProcess(Process.myPid());
                        return;
                    }
                }
            }
            if (previous != null) previous.uncaughtException(thread, failure);
        });
    }

    @Override public IBinder onBind(Intent intent) { return messenger.getBinder(); }

    @Override public boolean onUnbind(Intent intent) {
        for (int i = 0; i < routes.size(); ++i) routes.valueAt(i).close();
        routes.clear();
        return false;
    }

    private boolean receive(Message message) {
        int id = message.arg1;
        long endpoint = message.getData().getLong(ENDPOINT);
        Route route = routes.get(id);
        if (message.what == REMOVE) {
            if (route != null && route.endpoint == endpoint) {
                routes.remove(id);
                route.close();
            }
            return true;
        }
        if (message.what != UPDATE || message.replyTo == null) return false;
        if (route == null || route.endpoint != endpoint) {
            if (route != null) route.close();
            route = new Route(id, endpoint, message.replyTo);
            routes.put(id, route);
        }
        route.update(message.arg2);
        return true;
    }

    private final class Route {
        final int id;
        final long endpoint;
        final Messenger client;
        final SensorEventListener[] listeners = new SensorEventListener[TYPES.length];
        final Sensor[] sensors = new Sensor[TYPES.length];
        SensorManager manager;

        Route(int id, long endpoint, Messenger client) {
            this.id = id;
            this.endpoint = endpoint;
            this.client = client;
        }

        void send(int what, int value, long timestamp, float[] sample) {
            Message reply = Message.obtain(null, what, id, value);
            Bundle data = reply.getData();
            data.putLong(ENDPOINT, endpoint);
            if (sample != null) {
                data.putLong(TIMESTAMP, timestamp);
                data.putFloatArray(VALUES, new float[]{sample[0], sample[1], sample[2]});
            }
            try { client.send(reply); }
            catch (RemoteException ignored) {}
        }

        void update(int requested) {
            int capabilities = 0;
            InputDevice device = InputDevice.getDevice(id);
            if (device != null && device.supportsSource(InputDevice.SOURCE_SENSOR)) {
                if (manager == null) manager = device.getSensorManager();
                for (int i = 0; i < TYPES.length; ++i) {
                    sensors[i] = manager.getDefaultSensor(TYPES[i]);
                    if (sensors[i] != null) capabilities |= 1 << i;
                }
            }
            send(CAPABILITIES, capabilities, 0, null);
            for (int i = 0; i < TYPES.length; ++i) {
                boolean enabled = (requested & capabilities & (1 << i)) != 0;
                if (!enabled && listeners[i] != null) {
                    manager.unregisterListener(listeners[i]);
                    listeners[i] = null;
                } else if (enabled && listeners[i] == null) {
                    final int index = i;
                    SensorEventListener listener = new SensorEventListener() {
                        @Override public void onAccuracyChanged(Sensor sensor, int accuracy) {}
                        @Override public void onSensorChanged(SensorEvent event) {
                            if (listeners[index] == this && event.values.length >= 3)
                                send(SAMPLE, index, event.timestamp, event.values);
                        }
                    };
                    if (manager.registerListener(listener, sensors[i], SensorManager.SENSOR_DELAY_GAME, handler))
                        listeners[i] = listener;
                }
            }
        }

        void close() {
            for (int i = 0; i < listeners.length; ++i) {
                if (listeners[i] != null) manager.unregisterListener(listeners[i]);
                listeners[i] = null;
            }
        }
    }
}
