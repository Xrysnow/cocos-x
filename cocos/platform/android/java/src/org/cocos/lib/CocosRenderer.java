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

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
public class CocosRenderer implements GLSurfaceView.Renderer {
    // ===========================================================
    // Constants
    // ===========================================================

    private final static long NANOSECONDSPERSECOND = 1000000000L;
    private final static long NANOSECONDSPERMICROSECOND = 1000000L;

    // The final animation interval which is used in 'onDrawFrame'
    private static long sAnimationInterval = (long) (1.0f / 60f * CocosRenderer.NANOSECONDSPERSECOND);
    private static long FPS_CONTROL_THRESHOLD = (long) (1.0f / 1200.0f * CocosRenderer.NANOSECONDSPERSECOND);

    // ===========================================================
    // Fields
    // ===========================================================

    private long mLastTickInNanoSeconds;
    private int mScreenWidth;
    private int mScreenHeight;
    private static boolean gNativeInitialized = false;
    private static boolean gNativeIsPaused = false;
    private boolean mSurfaceCreated = false;

    // ===========================================================
    // Constructors
    // ===========================================================

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    public static void setAnimationInterval(float interval) {
        sAnimationInterval = (long) (interval * CocosRenderer.NANOSECONDSPERSECOND);
    }

    public void setScreenWidthAndHeight(final int surfaceWidth, final int surfaceHeight) {
        this.mScreenWidth = surfaceWidth;
        this.mScreenHeight = surfaceHeight;
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    public void onSurfaceCreated(final GL10 GL10, final EGLConfig EGLConfig) {
        CocosRenderer.nativeInit(this.mScreenWidth, this.mScreenHeight);
        this.mLastTickInNanoSeconds = System.nanoTime();

        boolean isWarmStart = !mSurfaceCreated;
        mSurfaceCreated = true;

        if (gNativeInitialized) {
            // This must be from an OpenGL context loss
            nativeOnContextLost(isWarmStart);
        } else {
            gNativeInitialized = true;
        }
    }

    @Override
    public void onSurfaceChanged(final GL10 GL10, final int width, final int height) {
        CocosRenderer.nativeOnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(final GL10 gl) {
        /*
         * Render time MUST be counted in, or the FPS will slower than appointed.
         */
        CocosRenderer.nativeRender();
        /*
         * No need to use algorithm in default(60,90,120... FPS) situation,
         * since onDrawFrame() was called by system 60 times per second by default.
         */
        if (CocosRenderer.sAnimationInterval > CocosRenderer.FPS_CONTROL_THRESHOLD) {
            final long interval = System.nanoTime() - this.mLastTickInNanoSeconds;

            if (interval < CocosRenderer.sAnimationInterval) {
                try {
                    Thread.sleep((CocosRenderer.sAnimationInterval - interval) / CocosRenderer.NANOSECONDSPERMICROSECOND);
                } catch (final Exception e) {
                }
            }

            this.mLastTickInNanoSeconds = System.nanoTime();
        }
    }

    // ===========================================================
    // Methods
    // ===========================================================

    private static native void nativeTouchesBegin(final int id, final float x, final float y);
    private static native void nativeTouchesEnd(final int id, final float x, final float y);
    private static native void nativeTouchesMove(final int[] ids, final float[] xs, final float[] ys);
    private static native void nativeTouchesCancel(final int[] ids, final float[] xs, final float[] ys);
    private static native boolean nativeKeyEvent(final int keyCode,boolean isPressed);
    private static native void nativeRender();
    private static native void nativeInit(final int width, final int height);
    private static native void nativeOnContextLost(final boolean isWarmStart);
    private static native void nativeOnSurfaceChanged(final int width, final int height);
    private static native void nativeOnPause();
    private static native void nativeOnResume();

    public void handleActionDown(final int id, final float x, final float y) {
        CocosRenderer.nativeTouchesBegin(id, x, y);
    }

    public void handleActionUp(final int id, final float x, final float y) {
        CocosRenderer.nativeTouchesEnd(id, x, y);
    }

    public void handleActionCancel(final int[] ids, final float[] xs, final float[] ys) {
        CocosRenderer.nativeTouchesCancel(ids, xs, ys);
    }

    public void handleActionMove(final int[] ids, final float[] xs, final float[] ys) {
        CocosRenderer.nativeTouchesMove(ids, xs, ys);
    }

    public void handleKeyDown(final int keyCode) {
        CocosRenderer.nativeKeyEvent(keyCode, true);
    }

    public void handleKeyUp(final int keyCode) {
        CocosRenderer.nativeKeyEvent(keyCode, false);
    }

    public void handleOnPause() {
        /**
         * onPause may be invoked before onSurfaceCreated,
         * and engine will be initialized correctly after
         * onSurfaceCreated is invoked. Can not invoke any
         * native method before onSurfaceCreated is invoked
         */
        if (!gNativeInitialized)
            return;

        CocosRenderer.nativeOnPause();
        gNativeIsPaused = true;
    }

    public void handleOnResume() {
        if (gNativeIsPaused) {
            CocosRenderer.nativeOnResume();
            gNativeIsPaused = false;
        }
    }

    private static native void nativeInsertText(final String text);
    private static native void nativeDeleteBackward(final int numChars);
    private static native String nativeGetContentText();

    public void handleInsertText(final String text) {
        CocosRenderer.nativeInsertText(text);
    }

    public void handleDeleteBackward(final int numChars) {
        CocosRenderer.nativeDeleteBackward(numChars);
    }

    public String getContentText() {
        return CocosRenderer.nativeGetContentText();
    }
}
