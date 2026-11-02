/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

package org.cocos.lib;

import android.util.Log;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.concurrent.CopyOnWriteArrayList;

public class GameControllerAdapter {
    private static final String TAG = "GameControllerAdapter";
    private static final CopyOnWriteArrayList<Runnable> sRunnableFrameStartList = new CopyOnWriteArrayList<>();
    // Only touched on the engine thread, alongside the native controller state.
    private static final Map<String, Control> buttons = new HashMap<>();
    private static final Map<String, Control> axes = new HashMap<>();

    /** Immutable source session; SDK listeners must retain this, never look up the latest view. */
    public static final class Source implements GameControllerDelegate.ControllerEventListener {
        private final CocosGLSurfaceView owner;
        private final long session;
        private volatile boolean valid = true;
        private volatile boolean resumed;
        private volatile long inputEpoch;

        public Source(CocosGLSurfaceView owner) {
            if (owner == null) throw new IllegalArgumentException("Controller source requires a RenderHost");
            this.owner = owner;
            this.session = owner.getSession();
        }

        public boolean isCurrent() {
            return valid && owner.isCurrentHost() && session == owner.getSession();
        }

        public boolean isResumed() {
            return isCurrent() && resumed;
        }

        public void setResumed(boolean value) {
            inputEpoch++;
            resumed = value;
        }

        public void invalidate() {
            valid = false;
            setResumed(false);
        }

        private void queueControl(Runnable task) {
            if (!isCurrent()) return;
            owner.queueEvent(() -> {
                if (isCurrent()) task.run();
            });
        }

        private void queueInput(Runnable task) {
            final long epoch = inputEpoch;
            if (!isCurrent() || !resumed) return;
            owner.queueInput(() -> {
                if (isCurrent() && resumed && epoch == inputEpoch) task.run();
            });
        }

        @Override
        public void onConnected(String vendorName, int controller) {
            queueControl(() -> nativeControllerConnected(vendorName, controller));
        }

        @Override
        public void onDisconnected(String vendorName, int controller) {
            queueControl(() -> {
                forgetController(buttons, vendorName, controller);
                forgetController(axes, vendorName, controller);
                nativeControllerDisconnected(vendorName, controller);
            });
        }

        @Override
        public void onButtonEvent(String vendorName, int controller, int button, boolean isPressed, float value, boolean isAnalog) {
            queueInput(() -> {
                if (isPressed) buttons.put(key(vendorName, controller, button), new Control(vendorName, controller, button, isAnalog));
                else buttons.remove(key(vendorName, controller, button));
                nativeControllerButtonEvent(vendorName, controller, button, isPressed, value, isAnalog);
            });
        }

        @Override
        public void onAxisEvent(String vendorName, int controller, int axisID, float value, boolean isAnalog) {
            queueInput(() -> {
                if (value != 0) axes.put(key(vendorName, controller, axisID), new Control(vendorName, controller, axisID, isAnalog));
                else axes.remove(key(vendorName, controller, axisID));
                nativeControllerAxisEvent(vendorName, controller, axisID, value, isAnalog);
            });
        }
    }

    private static final class Control {
        final String vendor;
        final int controller;
        final int code;
        final boolean analog;

        Control(String vendor, int controller, int code, boolean analog) {
            this.vendor = vendor;
            this.controller = controller;
            this.code = code;
            this.analog = analog;
        }
    }

    private static String key(String vendor, int controller, int code) {
        return vendor + ":" + controller + ":" + code;
    }

    static void cancelPendingInput() {
        for (Control control : buttons.values())
            nativeControllerButtonEvent(control.vendor, control.controller, control.code, false, 0, control.analog);
        for (Control control : axes.values())
            nativeControllerAxisEvent(control.vendor, control.controller, control.code, 0, control.analog);
        buttons.clear();
        axes.clear();
    }

    private static void forgetController(Map<String, Control> controls, String vendor, int controller) {
        Iterator<Control> iterator = controls.values().iterator();
        while (iterator.hasNext()) {
            Control control = iterator.next();
            if (control.controller == controller && control.vendor.equals(vendor)) iterator.remove();
        }
    }
    
    public static void addRunnableToFrameStartList(Runnable runnable) {
        sRunnableFrameStartList.add(runnable);
    }

    public static void removeRunnableFromFrameStartList(Runnable runnable) {
        sRunnableFrameStartList.remove(runnable);
    }

    public static void onDrawFrameStart() {
        for (Runnable runnable : sRunnableFrameStartList) runnable.run();
    }
    
    @Deprecated
    public static void onConnected(final String vendorName, final int controller)
    {
        rejectUnboundEvent();
    }
    
    @Deprecated
    public static void onDisconnected(final String vendorName, final int controller)
    {
        rejectUnboundEvent();
    }
    
    @Deprecated
    public static void onButtonEvent(final String vendorName, final int controller, final int button, final boolean isPressed, final float value, final boolean isAnalog)
    {
        rejectUnboundEvent();
    }
    
    @Deprecated
    public static void onAxisEvent(final String vendorName, final int controller, final int axisID, final float value, final boolean isAnalog)
    {
        rejectUnboundEvent();
    }

    private static void rejectUnboundEvent() {
        // All active adapters use Source. Untagged callbacks cannot be safely
        // attributed after recreation and must not target the current Activity.
        Log.w(TAG, "Controller event rejected: bind a Source to the originating RenderHost");
    }
    
    private static native void nativeControllerConnected(final String vendorName, final int controller);
    private static native void nativeControllerDisconnected(final String vendorName, final int controller);
    private static native void nativeControllerButtonEvent(final String vendorName, final int controller, final int button, final boolean isPressed, final float value, final boolean isAnalog);
    private static native void nativeControllerAxisEvent(final String vendorName, final int controller, final int axisID, final float value, final boolean isAnalog);
}
