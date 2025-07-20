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

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.inputmethod.InputMethodManager;

import java.util.concurrent.CountDownLatch;

public class CocosGLSurfaceView extends GLSurfaceView {
    // ===========================================================
    // Constants
    // ===========================================================

    private static final String TAG = CocosGLSurfaceView.class.getSimpleName();

    private final static int HANDLER_OPEN_IME_KEYBOARD = 2;
    private final static int HANDLER_CLOSE_IME_KEYBOARD = 3;

    // ===========================================================
    // Fields
    // ===========================================================

    // TODO Static handler -> Potential leak!
    private static Handler sHandler;

    private static CocosGLSurfaceView mGLSurfaceView;
    private static TextInputWrapper sTextInputWraper;

    private CocosRenderer mRenderer;
    private CocosEditBox mEditText;

    private boolean mSoftKeyboardShown = false;
    private boolean mMultipleTouchEnabled = true;

    private CountDownLatch mNativePauseComplete;

    public boolean isSoftKeyboardShown() {
        return mSoftKeyboardShown;
    }

    public void setSoftKeyboardShown(boolean softKeyboardShown) {
        this.mSoftKeyboardShown = softKeyboardShown;
    }

    public boolean isMultipleTouchEnabled() {
        return mMultipleTouchEnabled;
    }

    public void setMultipleTouchEnabled(boolean multipleTouchEnabled) {
        this.mMultipleTouchEnabled = multipleTouchEnabled;
    }

    // ===========================================================
    // Constructors
    // ===========================================================

    public CocosGLSurfaceView(final Context context) {
        super(context);

        this.initView();
    }

    public CocosGLSurfaceView(final Context context, final AttributeSet attrs) {
        super(context, attrs);

        this.initView();
    }

    protected void initView() {
        this.setEGLContextClientVersion(2);
        this.setFocusableInTouchMode(true);

        CocosGLSurfaceView.mGLSurfaceView = this;
        CocosGLSurfaceView.sTextInputWraper = new TextInputWrapper(this);

        CocosGLSurfaceView.sHandler = new Handler() {
            @Override
            public void handleMessage(final Message msg) {
                switch (msg.what) {
                    case HANDLER_OPEN_IME_KEYBOARD:
                        if (null != CocosGLSurfaceView.this.mEditText) {
                            CocosGLSurfaceView.this.mEditText.setVisibility(View.VISIBLE);
                            if (CocosGLSurfaceView.this.mEditText.requestFocus()) {
                                CocosGLSurfaceView.this.mEditText.removeTextChangedListener(CocosGLSurfaceView.sTextInputWraper);
                                CocosGLSurfaceView.this.mEditText.setText("");
                                final String text = (String) msg.obj;
                                CocosGLSurfaceView.this.mEditText.append(text);
                                CocosGLSurfaceView.sTextInputWraper.setOriginText(text);
                                CocosGLSurfaceView.this.mEditText.addTextChangedListener(CocosGLSurfaceView.sTextInputWraper);
                                final InputMethodManager imm = (InputMethodManager) CocosGLSurfaceView.mGLSurfaceView.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                                imm.showSoftInput(CocosGLSurfaceView.this.mEditText, 0);
                                Log.d("GLSurfaceView", "showSoftInput");
                            }
                        }
                        break;

                    case HANDLER_CLOSE_IME_KEYBOARD:
                        if (null != CocosGLSurfaceView.this.mEditText) {
                            CocosGLSurfaceView.this.mEditText.removeTextChangedListener(CocosGLSurfaceView.sTextInputWraper);
                            final InputMethodManager imm = (InputMethodManager) CocosGLSurfaceView.mGLSurfaceView.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                            imm.hideSoftInputFromWindow(CocosGLSurfaceView.this.mEditText.getWindowToken(), 0);
                            CocosGLSurfaceView.this.requestFocus();
                            // can take effect after GLSurfaceView has focus
                            CocosGLSurfaceView.this.mEditText.setVisibility(View.GONE);
                            ((CocosActivity)CocosGLSurfaceView.mGLSurfaceView.getContext()).hideVirtualButton();
                            Log.d("GLSurfaceView", "HideSoftInput");
                        }
                        break;
                }
            }
        };
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================


       public static CocosGLSurfaceView getInstance() {
       return mGLSurfaceView;
       }

       public static void queueAccelerometer(final float x, final float y, final float z, final long timestamp) {
       mGLSurfaceView.queueEvent(new Runnable() {
        @Override
            public void run() {
                CocosAccelerometer.onSensorChanged(x, y, z, timestamp);
        }
        });
    }

    @Override
    public void setRenderer(GLSurfaceView.Renderer renderer) {
        this.mRenderer = (CocosRenderer) renderer;
        super.setRenderer(this.mRenderer);
    }

    public void setCocosRenderer(final CocosRenderer renderer) {
        this.mRenderer = renderer;
        this.setRenderer(this.mRenderer);
    }

    private String getContentText() {
        return this.mRenderer.getContentText();
    }

    public CocosEditBox getEditText() {
        return this.mEditText;
    }

    public CocosEditBox getCocosEditText() {
        return this.mEditText;
    }
    public void setEditText(final CocosEditBox pEditText) {
        this.mEditText = pEditText;
        if (null != this.mEditText && null != CocosGLSurfaceView.sTextInputWraper) {
            this.mEditText.setOnEditorActionListener(CocosGLSurfaceView.sTextInputWraper);
            this.requestFocus();
        }
    }

    public void setCocosEditText(final CocosEditBox pEditText) {
        this.setEditText(pEditText);
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    public boolean onTouchEvent(final MotionEvent pMotionEvent) {
        // these data are used in ACTION_MOVE and ACTION_CANCEL
        final int pointerNumber = pMotionEvent.getPointerCount();
        final int[] ids = new int[pointerNumber];
        final float[] xs = new float[pointerNumber];
        final float[] ys = new float[pointerNumber];

        if (mSoftKeyboardShown){
            InputMethodManager imm = (InputMethodManager)this.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
            View view = ((Activity)this.getContext()).getCurrentFocus();
            if (null != view) {
                imm.hideSoftInputFromWindow(view.getWindowToken(),0);
            }
            this.requestFocus();
            mSoftKeyboardShown = false;
        }

        for (int i = 0; i < pointerNumber; i++) {
            ids[i] = pMotionEvent.getPointerId(i);
            xs[i] = pMotionEvent.getX(i);
            ys[i] = pMotionEvent.getY(i);
        }

        switch (pMotionEvent.getAction() & MotionEvent.ACTION_MASK) {
            case MotionEvent.ACTION_POINTER_DOWN:
                final int indexPointerDown = pMotionEvent.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                if (!mMultipleTouchEnabled && indexPointerDown != 0) {
                    break;
                }
                final int idPointerDown = pMotionEvent.getPointerId(indexPointerDown);
                final float xPointerDown = pMotionEvent.getX(indexPointerDown);
                final float yPointerDown = pMotionEvent.getY(indexPointerDown);

                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        CocosGLSurfaceView.this.mRenderer.handleActionDown(idPointerDown, xPointerDown, yPointerDown);
                    }
                });
                break;

            case MotionEvent.ACTION_DOWN:
                // there are only one finger on the screen
                final int idDown = pMotionEvent.getPointerId(0);
                final float xDown = xs[0];
                final float yDown = ys[0];

                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        CocosGLSurfaceView.this.mRenderer.handleActionDown(idDown, xDown, yDown);
                    }
                });
                break;

            case MotionEvent.ACTION_MOVE:
                if (!mMultipleTouchEnabled) {
                    // handle only touch with id == 0
                    for (int i = 0; i < pointerNumber; i++) {
                        if (ids[i] == 0) {
                            final int[] idsMove = new int[]{0};
                            final float[] xsMove = new float[]{xs[i]};
                            final float[] ysMove = new float[]{ys[i]};
                            this.queueEvent(new Runnable() {
                                @Override
                                public void run() {
                                    CocosGLSurfaceView.this.mRenderer.handleActionMove(idsMove, xsMove, ysMove);
                                }
                            });
                            break;
                        }
                    }
                } else {
                    this.queueEvent(new Runnable() {
                        @Override
                        public void run() {
                            CocosGLSurfaceView.this.mRenderer.handleActionMove(ids, xs, ys);
                        }
                    });
                }
                break;

            case MotionEvent.ACTION_POINTER_UP:
                final int indexPointUp = pMotionEvent.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                if (!mMultipleTouchEnabled && indexPointUp != 0) {
                    break;
                }
                final int idPointerUp = pMotionEvent.getPointerId(indexPointUp);
                final float xPointerUp = pMotionEvent.getX(indexPointUp);
                final float yPointerUp = pMotionEvent.getY(indexPointUp);

                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        CocosGLSurfaceView.this.mRenderer.handleActionUp(idPointerUp, xPointerUp, yPointerUp);
                    }
                });
                break;

            case MotionEvent.ACTION_UP:
                // there are only one finger on the screen
                final int idUp = pMotionEvent.getPointerId(0);
                final float xUp = xs[0];
                final float yUp = ys[0];

                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        CocosGLSurfaceView.this.mRenderer.handleActionUp(idUp, xUp, yUp);
                    }
                });
                break;

            case MotionEvent.ACTION_CANCEL:
                if (!mMultipleTouchEnabled) {
                    // handle only touch with id == 0
                    for (int i = 0; i < pointerNumber; i++) {
                        if (ids[i] == 0) {
                            final int[] idsCancel = new int[]{0};
                            final float[] xsCancel = new float[]{xs[i]};
                            final float[] ysCancel = new float[]{ys[i]};
                            this.queueEvent(new Runnable() {
                                @Override
                                public void run() {
                                    CocosGLSurfaceView.this.mRenderer.handleActionCancel(idsCancel, xsCancel, ysCancel);
                                }
                            });
                            break;
                        }
                    }
                } else {
                    this.queueEvent(new Runnable() {
                        @Override
                        public void run() {
                            CocosGLSurfaceView.this.mRenderer.handleActionCancel(ids, xs, ys);
                        }
                    });
                }
                break;
        }

        /*
        if (BuildConfig.DEBUG) {
            CocosGLSurfaceView.dumpMotionEvent(pMotionEvent);
        }
        */
        return true;
    }

    /*
     * This function is called before CocosRenderer.nativeInit(), so the
     * width and height is correct.
     */
    @Override
    protected void onSizeChanged(final int pNewSurfaceWidth, final int pNewSurfaceHeight, final int pOldSurfaceWidth, final int pOldSurfaceHeight) {
        if(!this.isInEditMode()) {
            this.mRenderer.setScreenWidthAndHeight(pNewSurfaceWidth, pNewSurfaceHeight);
        }
    }

    protected boolean isIgnoredKey(final int keyCode) {
        if ((keyCode <= KeyEvent.KEYCODE_HOME)
                || (keyCode == KeyEvent.KEYCODE_CALL)
                || (keyCode == KeyEvent.KEYCODE_ENDCALL)
                || (keyCode == KeyEvent.KEYCODE_VOLUME_UP)
                || (keyCode == KeyEvent.KEYCODE_VOLUME_DOWN)
                || (keyCode == KeyEvent.KEYCODE_POWER)
                || (keyCode == KeyEvent.KEYCODE_CAMERA)
                || (keyCode == KeyEvent.KEYCODE_SYM)
                || (keyCode == KeyEvent.KEYCODE_EXPLORER)
                || (keyCode == KeyEvent.KEYCODE_ENVELOPE)
                || (keyCode == KeyEvent.KEYCODE_NUM)
                || (keyCode == KeyEvent.KEYCODE_HEADSETHOOK)
                || (keyCode == KeyEvent.KEYCODE_FOCUS)
                || (keyCode == KeyEvent.KEYCODE_MUTE)
                || (keyCode == KeyEvent.KEYCODE_PICTSYMBOLS)
                || (keyCode == KeyEvent.KEYCODE_SWITCH_CHARSET)
                || (keyCode == KeyEvent.KEYCODE_NUM_LOCK)
                || (KeyEvent.KEYCODE_VOLUME_MUTE <= keyCode && keyCode <= KeyEvent.KEYCODE_APP_SWITCH)
                || (KeyEvent.KEYCODE_LANGUAGE_SWITCH <= keyCode && keyCode <= KeyEvent.KEYCODE_HELP)
                || (KeyEvent.KEYCODE_MEDIA_SKIP_FORWARD <= keyCode)
            )
        {
            return true;
        }
        return false;
    }

    @Override
    public boolean onKeyDown(final int pKeyCode, final KeyEvent pKeyEvent) {
        if (!isIgnoredKey(pKeyCode)) {
            this.queueEvent(new Runnable() {
                @Override
                public void run() {
                    CocosGLSurfaceView.this.mRenderer.handleKeyDown(pKeyCode);
                }
            });
            return true;
        }
        return super.onKeyDown(pKeyCode, pKeyEvent);
    }

    @Override
    public boolean onKeyUp(final int keyCode, KeyEvent event) {
        if (!isIgnoredKey(keyCode)) {
            this.queueEvent(new Runnable() {
                @Override
                public void run() {
                    CocosGLSurfaceView.this.mRenderer.handleKeyUp(keyCode);
                }
            });
            return true;
        }
        return super.onKeyUp(keyCode, event);
    }

    // ===========================================================
    // Methods
    // ===========================================================

    public void handleOnResume() {
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                CocosGLSurfaceView.this.mRenderer.handleOnResume();
            }
        });
    }

    public void handleOnPause() {
        mNativePauseComplete = new CountDownLatch(1);

        CountDownLatch complete = mNativePauseComplete;
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                CocosGLSurfaceView.this.mRenderer.handleOnPause();
                complete.countDown();
            }
        });
    }

    public void waitForPauseToComplete() {
        while (mNativePauseComplete.getCount() > 0) {
            try {
                mNativePauseComplete.await();
            } catch (InterruptedException e) {
            }
        }
    }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================

    public static void openIMEKeyboard() {
        final Message msg = new Message();
        msg.what = CocosGLSurfaceView.HANDLER_OPEN_IME_KEYBOARD;
        msg.obj = CocosGLSurfaceView.mGLSurfaceView.getContentText();
        CocosGLSurfaceView.sHandler.sendMessage(msg);
    }

    public static void closeIMEKeyboard() {
        final Message msg = new Message();
        msg.what = CocosGLSurfaceView.HANDLER_CLOSE_IME_KEYBOARD;
        CocosGLSurfaceView.sHandler.sendMessage(msg);
    }

    public void insertText(final String pText) {
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                CocosGLSurfaceView.this.mRenderer.handleInsertText(pText);
            }
        });
    }

    public void deleteBackward(int numChars) {
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                CocosGLSurfaceView.this.mRenderer.handleDeleteBackward(numChars);
            }
        });
    }

    private static void dumpMotionEvent(final MotionEvent event) {
        final String names[] = { "DOWN", "UP", "MOVE", "CANCEL", "OUTSIDE", "POINTER_DOWN", "POINTER_UP", "7?", "8?", "9?" };
        final StringBuilder sb = new StringBuilder();
        final int action = event.getAction();
        final int actionCode = action & MotionEvent.ACTION_MASK;
        sb.append("event ACTION_").append(names[actionCode]);
        if (actionCode == MotionEvent.ACTION_POINTER_DOWN || actionCode == MotionEvent.ACTION_POINTER_UP) {
            sb.append("(pid ").append(action >> MotionEvent.ACTION_POINTER_INDEX_SHIFT);
            sb.append(")");
        }
        sb.append("[");
        for (int i = 0; i < event.getPointerCount(); i++) {
            sb.append("#").append(i);
            sb.append("(pid ").append(event.getPointerId(i));
            sb.append(")=").append((int) event.getX(i));
            sb.append(",").append((int) event.getY(i));
            if (i + 1 < event.getPointerCount()) {
                sb.append(";");
            }
        }
        sb.append("]");
        Log.d(CocosGLSurfaceView.TAG, sb.toString());
    }
}
