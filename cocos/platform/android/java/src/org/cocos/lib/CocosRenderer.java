/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/** Input JNI adapter. Frame scheduling and window ownership live in CocosRenderHost. */
public class CocosRenderer {
    private final Map<Integer, float[]> touches = new HashMap<>();
    private final Set<Integer> keys = new HashSet<>();
    public static void setAnimationInterval(float interval) {
        CocosRenderHost.setAnimationInterval(interval);
    }

    private static native void nativeTouchesBegin(final int id, final float x, final float y);
    private static native void nativeTouchesEnd(final int id, final float x, final float y);
    private static native void nativeTouchesMove(final int[] ids, final float[] xs, final float[] ys);
    private static native void nativeTouchesCancel(final int[] ids, final float[] xs, final float[] ys);
    private static native boolean nativeKeyEvent(final int keyCode,boolean isPressed);

    public void handleActionDown(final int id, final float x, final float y) {
        touches.put(id, new float[] {x, y});
        CocosRenderer.nativeTouchesBegin(id, x, y);
    }

    public void handleActionUp(final int id, final float x, final float y) {
        if (touches.remove(id) == null) return;
        CocosRenderer.nativeTouchesEnd(id, x, y);
    }

    public void handleActionCancel(final int[] ids, final float[] xs, final float[] ys) {
        for (int id : ids) touches.remove(id);
        CocosRenderer.nativeTouchesCancel(ids, xs, ys);
    }

    public void handleActionMove(final int[] ids, final float[] xs, final float[] ys) {
        int count = 0;
        for (int id : ids) if (touches.containsKey(id)) count++;
        if (count == 0) return;
        final int[] activeIds = new int[count];
        final float[] activeXs = new float[count];
        final float[] activeYs = new float[count];
        int active = 0;
        for (int i = 0; i < ids.length; i++) {
            if (touches.containsKey(ids[i])) {
                touches.put(ids[i], new float[] {xs[i], ys[i]});
                activeIds[active] = ids[i];
                activeXs[active] = xs[i];
                activeYs[active++] = ys[i];
            }
        }
        CocosRenderer.nativeTouchesMove(activeIds, activeXs, activeYs);
    }

    public void handleKeyDown(final int keyCode) {
        keys.add(keyCode);
        CocosRenderer.nativeKeyEvent(keyCode, true);
    }

    public void handleKeyUp(final int keyCode) {
        if (!keys.remove(keyCode)) return;
        CocosRenderer.nativeKeyEvent(keyCode, false);
    }

    void cancelPendingInput() {
        final int[] ids = new int[touches.size()];
        final float[] xs = new float[ids.length];
        final float[] ys = new float[ids.length];
        int i = 0;
        for (Map.Entry<Integer, float[]> entry : touches.entrySet()) {
            ids[i] = entry.getKey();
            xs[i] = entry.getValue()[0];
            ys[i] = entry.getValue()[1];
            i++;
        }
        if (ids.length != 0) nativeTouchesCancel(ids, xs, ys);
        touches.clear();
        for (int key : keys) nativeKeyEvent(key, false);
        keys.clear();
    }

    private static native void nativeInsertText(final String text);
    private static native void nativeDeleteBackward(final int numChars);
    private static native void nativeIMEClosed();
    private static native String nativeGetContentText();

    public void handleInsertText(final String text) {
        CocosRenderer.nativeInsertText(text);
    }

    public void handleDeleteBackward(final int numChars) {
        CocosRenderer.nativeDeleteBackward(numChars);
    }

    void handleIMEClosed() {
        CocosRenderer.nativeIMEClosed();
    }

    public String getContentText() {
        return CocosRenderer.nativeGetContentText();
    }
}
