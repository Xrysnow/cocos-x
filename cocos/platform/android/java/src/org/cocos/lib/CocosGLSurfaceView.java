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
import android.graphics.Insets;
import android.graphics.Matrix;
import android.graphics.Rect;
import android.os.Build;
import android.text.InputType;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.os.Handler;
import android.os.Looper;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowInsets;
import android.view.inputmethod.InputMethodManager;
import android.view.inputmethod.InputConnection;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.CursorAnchorInfo;
import java.util.Objects;


/** Compatibility name: this view no longer creates an EGL context. */
public class CocosGLSurfaceView extends SurfaceView implements SurfaceHolder.Callback {
    // ===========================================================
    // Constants
    // ===========================================================

    private static final String TAG = CocosGLSurfaceView.class.getSimpleName();

    // ===========================================================
    // Fields
    // ===========================================================

    private Handler mImeHandler;

    private static volatile CocosGLSurfaceView mGLSurfaceView;
    private TextInputWrapper mTextInputWrapper;

    private CocosRenderer mRenderer;
    private CocosEditBox mEditText;

    private boolean mSoftKeyboardShown = false;
    private boolean mMultipleTouchEnabled = true;

    private CocosRenderHost mRenderHost;

    // These values mirror TextInputCommandAction and TextInputCloseReason.
    private static final int TEXT_BACKSPACE = 0;
    private static final int TEXT_DELETE = 1;
    private static final int TEXT_LEFT = 2;
    private static final int TEXT_RIGHT = 3;
    private static final int TEXT_UP = 4;
    private static final int TEXT_DOWN = 5;
    private static final int TEXT_LINE_START = 6;
    private static final int TEXT_LINE_END = 7;
    private static final int TEXT_SELECT_ALL = 8;
    private static final int TEXT_NEWLINE = 9;
    private static final int TEXT_DONE = 10;
    private static final int TEXT_SEARCH = 11;
    private static final int TEXT_SEND = 12;
    private static final int TEXT_NEXT = 13;
    private static final int TEXT_GO = 14;
    private static final int TEXT_CANCEL = 15;
    private static final int CLOSE_REQUESTED = 0;
    private static final int CLOSE_REPLACED = 1;
    private static final int CLOSE_FOCUS_LOST = 2;
    private static final int CLOSE_ACTIVATION_FAILED = 3;
    private static final int CLOSE_NATIVE_ENDED = 4;

    // These fields live on the Android UI thread.
    private long mTextInputSession;
    private long mTextInputGeneration;
    private boolean mTextInputMultiline;
    private boolean mHasCaret;
    private float mCaretX;
    private float mCaretY;
    private float mCaretHeight;
    private int mCursorUpdateMode;
    private Boolean mLastKeyboardVisibility;
    private Rect mLastKeyboardOcclusion;
    private float mLastKeyboardDensity;
    private boolean mWaitingForSnapshot;

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
        mRenderHost = new CocosRenderHost((Activity) getContext());
        getHolder().addCallback(this);
        this.setFocusableInTouchMode(true);

        CocosGLSurfaceView.mGLSurfaceView = this;
        mTextInputWrapper = new TextInputWrapper(this);

        mImeHandler = new Handler(Looper.getMainLooper());
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================


       public static CocosGLSurfaceView getInstance() {
       return mGLSurfaceView;
       }

       public static void queueAccelerometer(final float x, final float y, final float z, final long timestamp) {
       if (mGLSurfaceView == null) return;
       mGLSurfaceView.queueInput(new Runnable() {
        @Override
            public void run() {
                CocosAccelerometer.onSensorChanged(x, y, z, timestamp);
        }
        });
    }

    public void setRenderer(CocosRenderer renderer) {
        this.mRenderer = renderer;
    }

    public void setCocosRenderer(final CocosRenderer renderer) {
        this.mRenderer = renderer;
        this.setRenderer(this.mRenderer);
    }

    public CocosEditBox getEditText() {
        return this.mEditText;
    }

    public CocosEditBox getCocosEditText() {
        return this.mEditText;
    }
    public void setEditText(final CocosEditBox pEditText) {
        this.mEditText = pEditText;
        if (null != this.mEditText && null != mTextInputWrapper) {
            this.mEditText.setOnEditorActionListener(mTextInputWrapper);
            this.mEditText.setOnFocusChangeListener((view, focused) -> {
                if (!focused) dismissTextInput(CLOSE_FOCUS_LOST);
            });
            getViewTreeObserver().addOnGlobalLayoutListener(() -> {
                if (mTextInputSession == 0) return;
                refreshTextInputInsets(getRootWindowInsets());
                if ((mCursorUpdateMode & InputConnection.CURSOR_UPDATE_MONITOR) != 0) updateTextInputCaret();
            });
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

        if (mSoftKeyboardShown && mTextInputSession == 0){
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

                this.queueInput(new Runnable() {
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

                this.queueInput(new Runnable() {
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
                            this.queueInput(new Runnable() {
                                @Override
                                public void run() {
                                    CocosGLSurfaceView.this.mRenderer.handleActionMove(idsMove, xsMove, ysMove);
                                }
                            });
                            break;
                        }
                    }
                } else {
                    this.queueInput(new Runnable() {
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

                this.queueInput(new Runnable() {
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

                this.queueInput(new Runnable() {
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
                            this.queueInput(new Runnable() {
                                @Override
                                public void run() {
                                    CocosGLSurfaceView.this.mRenderer.handleActionCancel(idsCancel, xsCancel, ysCancel);
                                }
                            });
                            break;
                        }
                    }
                } else {
                    this.queueInput(new Runnable() {
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

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        mRenderHost.surfaceCreated();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        cancelPendingInput();
        mRenderHost.surfaceChanged(holder.getSurface(), width, height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        dismissTextInput(CLOSE_NATIVE_ENDED);
        cancelPendingInput();
        mRenderHost.surfaceDestroyed();
    }

    public void queueEvent(Runnable event) {
        mRenderHost.queueEvent(event);
    }

    void queueInput(Runnable event) {
        mRenderHost.queueInput(event);
    }

    boolean isCurrentHost() {
        return mGLSurfaceView == this && mRenderHost.isCurrent();
    }

    long getInputEpoch() {
        return mRenderHost.getInputEpoch();
    }

    long getSession() {
        return mRenderHost.getSession();
    }

    boolean isInputCurrent(long epoch) {
        return isCurrentHost() && mRenderHost.isInputCurrent(epoch);
    }

    boolean decideNavigation(java.util.concurrent.Callable<Boolean> decision) {
        return mRenderHost.decideNavigation(decision);
    }

    void cancelPendingInput() {
        mRenderHost.cancelInput(() -> {
            if (mRenderer != null) mRenderer.cancelPendingInput();
            GameControllerAdapter.cancelPendingInput();
        });
    }

    private void dismissTextInput(int reason) {
        final long session = mTextInputSession;
        if (session == 0) return;
        if (reason == CLOSE_REQUESTED) mTextInputWrapper.flushCommittedText();
        mTextInputWrapper.finishObservation();
        mTextInputSession = 0;
        mCursorUpdateMode = 0;
        mHasCaret = false;
        mLastKeyboardVisibility = null;
        mLastKeyboardOcclusion = null;
        mWaitingForSnapshot = false;
        mTextInputWrapper.deactivate();
        mEditText.removeTextChangedListener(mTextInputWrapper);
        final InputMethodManager imm = textInputManager();
        if (imm != null) imm.hideSoftInputFromWindow(mEditText.getWindowToken(), 0);
        mEditText.clearFocus();
        mEditText.setVisibility(View.GONE);
        mEditText.getText().clear();
        nativeTextInputClosed(session, reason);
    }

    boolean isIMEEditor(CocosEditBox editor) {
        return mTextInputSession != 0 && mEditText == editor && isCurrentHost();
    }

    InputConnection wrapInputConnection(InputConnection connection) {
        return connection == null ? null : mTextInputWrapper.wrap(connection);
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
            this.queueInput(new Runnable() {
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
            this.queueInput(new Runnable() {
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
        mRenderHost.setResumed(true);
    }

    public void handleOnPause() {
        cancelPendingInput();
        mRenderHost.setResumed(false);
        dismissTextInput(CLOSE_FOCUS_LOST);
    }

    void handleWindowFocusChanged(boolean hasFocus) {
        mRenderHost.setFocused(hasFocus);
        if (!hasFocus) {
            dismissTextInput(CLOSE_FOCUS_LOST);
            cancelPendingInput();
        }
    }

    public void waitForPauseToComplete() {
        mRenderHost.waitForPause();
    }

    public void closeRenderHost(boolean finalClose) {
        dismissTextInput(CLOSE_NATIVE_ENDED);
        cancelPendingInput();
        mRenderHost.close(finalClose);
        if (mEditText != null) mEditText.setOnEditorActionListener(null);
        if (mEditText != null) mEditText.setOnFocusChangeListener(null);
        if (mGLSurfaceView == this) {
            mGLSurfaceView = null;
        }
    }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================

    private static native void nativeTextInputCommit(long session, String text);
    private static native boolean nativeTextInputEdit(long session, long epoch, long revision, long transaction,
            long origin, String previous, String current, int anchor, int focus);
    private static native void nativeTextInputPreedit(long session, String text, int phase, int anchor, int focus);
    private static native void nativeTextInputCommand(long session, int action);
    private static native void nativeTextInputClosed(long session, int reason);
    private static native void nativeTextInputKeyboardState(long session, int composing, boolean visible,
            boolean hasOcclusion, float x, float y, float width, float height);

    public static boolean activateTextInput(long session, int purpose, int capitalization,
            int returnAction, boolean multiline, int autocorrect, boolean initialSnapshot, boolean observePreedit) {
        final CocosGLSurfaceView view = mGLSurfaceView;
        if (view == null) return false;
        final long generation = view.mRenderHost.getTextInputGeneration();
        return view.mImeHandler.post(() -> {
            if (!view.isCurrentHost() || !view.mRenderHost.isTextInputCurrent(generation) || view.mEditText == null) {
                nativeTextInputClosed(session, CLOSE_ACTIVATION_FAILED);
                return;
            }
            view.beginTextInput(session, generation, purpose, capitalization, returnAction, multiline, autocorrect,
                    initialSnapshot, observePreedit);
        });
    }

    private void beginTextInput(long session, long generation, int purpose, int capitalization,
            int returnAction, boolean multiline, int autocorrect, boolean initialSnapshot, boolean observePreedit) {
        if (mTextInputSession != 0) dismissTextInput(CLOSE_REPLACED);
        mTextInputSession = session;
        mTextInputGeneration = generation;
        mTextInputMultiline = multiline;
        mWaitingForSnapshot = initialSnapshot;

        mEditText.setShowSoftInputOnFocus(false);
        mEditText.setInputType(textInputType(purpose, capitalization, multiline, autocorrect));
        final int action = returnAction == 0 && multiline ? EditorInfo.IME_ACTION_NONE : RETURN_ACTIONS[returnAction];
        mEditText.setImeOptions(action | EditorInfo.IME_FLAG_NO_EXTRACT_UI | EditorInfo.IME_FLAG_NO_PERSONALIZED_LEARNING);
        mEditText.setText("");
        mTextInputWrapper.activate(observePreedit);
        mEditText.addTextChangedListener(mTextInputWrapper);
        mEditText.setVisibility(View.VISIBLE);
        if (!mEditText.requestFocus()) {
            dismissTextInput(CLOSE_ACTIVATION_FAILED);
            return;
        }
        if (!initialSnapshot) restartTextInput(true);
        refreshTextInputInsets(getRootWindowInsets());
    }

    private void restartTextInput(boolean showKeyboard) {
        final InputMethodManager imm = textInputManager();
        if (imm == null) return;
        mCursorUpdateMode = 0;
        imm.restartInput(mEditText);
        if (showKeyboard) imm.showSoftInput(mEditText, 0);
    }

    private static final int[] RETURN_ACTIONS = {
        EditorInfo.IME_ACTION_DONE, EditorInfo.IME_ACTION_DONE, EditorInfo.IME_ACTION_SEARCH,
        EditorInfo.IME_ACTION_SEND, EditorInfo.IME_ACTION_NEXT, EditorInfo.IME_ACTION_GO
    };
    private static final int[] PURPOSE_INPUT_TYPES = {
        InputType.TYPE_CLASS_TEXT,
        InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PERSON_NAME,
        InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS,
        InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_URI,
        InputType.TYPE_CLASS_PHONE,
        InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_SIGNED,
        InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_SIGNED | InputType.TYPE_NUMBER_FLAG_DECIMAL,
        InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD
    };

    private static int textInputType(int purpose, int capitalization, boolean multiline, int autocorrect) {
        int type = PURPOSE_INPUT_TYPES[purpose];
        if ((type & InputType.TYPE_MASK_CLASS) != InputType.TYPE_CLASS_TEXT || purpose == 7) return type;
        if (multiline) type |= InputType.TYPE_TEXT_FLAG_MULTI_LINE;
        if (autocorrect == 0) type |= InputType.TYPE_TEXT_FLAG_NO_SUGGESTIONS;
        else if (autocorrect == 1) type |= InputType.TYPE_TEXT_FLAG_AUTO_CORRECT;
        if (capitalization == 2) type |= InputType.TYPE_TEXT_FLAG_CAP_SENTENCES;
        if (capitalization == 3) type |= InputType.TYPE_TEXT_FLAG_CAP_WORDS;
        if (capitalization == 4) type |= InputType.TYPE_TEXT_FLAG_CAP_CHARACTERS;
        return type;
    }

    public static boolean closeTextInput(long session) {
        final CocosGLSurfaceView view = mGLSurfaceView;
        return view != null && view.mImeHandler.post(() -> {
            if (view.mTextInputSession == session) view.dismissTextInput(CLOSE_REQUESTED);
            else nativeTextInputClosed(session, CLOSE_REQUESTED);
        });
    }

    public static boolean requestTextInputKeyboard(long session, boolean visible) {
        final CocosGLSurfaceView view = mGLSurfaceView;
        return view != null && view.mImeHandler.post(() -> {
            if (!view.isTextInputCurrent(session)) return;
            final InputMethodManager imm = view.textInputManager();
            if (imm == null) return;
            if (visible) imm.showSoftInput(view.mEditText, 0);
            else imm.hideSoftInputFromWindow(view.mEditText.getWindowToken(), 0);
        });
    }

    public static boolean cancelTextInputComposition(long session) {
        final CocosGLSurfaceView view = mGLSurfaceView;
        return view != null && view.mImeHandler.post(() -> {
            if (!view.isTextInputCurrent(session)) return;
            if (view.mTextInputWrapper.cancelComposition()) view.restartTextInput(false);
            else view.dismissTextInput(CLOSE_ACTIVATION_FAILED);
        });
    }

    private InputMethodManager textInputManager() {
        return (InputMethodManager) getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
    }

    public static boolean hasTextInputKeyboardVisibility() {
        return Build.VERSION.SDK_INT >= Build.VERSION_CODES.R;
    }

    void refreshTextInputInsets(WindowInsets insets) {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.R || insets == null ||
                !isTextInputCurrent(mTextInputSession)) return;
        final boolean visible = insets.isVisible(WindowInsets.Type.ime());
        final Rect occlusion = visible ? textInputOcclusion(insets.getInsets(WindowInsets.Type.ime())) : new Rect();
        final float density = getResources().getDisplayMetrics().density;
        if (mLastKeyboardVisibility != null && mLastKeyboardVisibility == visible &&
                Objects.equals(mLastKeyboardOcclusion, occlusion) && mLastKeyboardDensity == density) return;
        mLastKeyboardVisibility = visible;
        mLastKeyboardOcclusion = occlusion;
        mLastKeyboardDensity = density;
        nativeTextInputKeyboardState(mTextInputSession, mTextInputWrapper.compositionKnowledge(), visible, occlusion != null,
                occlusion != null ? occlusion.left / density : 0,
                occlusion != null ? occlusion.top / density : 0,
                occlusion != null ? occlusion.width() / density : 0,
                occlusion != null ? occlusion.height() / density : 0);
    }

    private Rect textInputOcclusion(Insets insets) {
        // Insets expose the bottom strip of a docked keyboard. A floating IME
        // can be visible without giving an edge inset.
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.R || insets.bottom <= 0 ||
                insets.top != 0 || insets.left != 0 || insets.right != 0 ||
                getWidth() <= 0 || getHeight() <= 0) return null;
        final Rect bounds = ((Activity) getContext()).getWindowManager().getCurrentWindowMetrics().getBounds();
        final Rect occlusion = new Rect(bounds.left, Math.max(bounds.top, bounds.bottom - insets.bottom),
                bounds.right, bounds.bottom);
        final int[] surface = new int[2];
        getLocationOnScreen(surface);
        if (occlusion.intersect(surface[0], surface[1], surface[0] + getWidth(), surface[1] + getHeight())) {
            occlusion.offset(-surface[0], -surface[1]);
        } else {
            occlusion.setEmpty();
        }
        return occlusion;
    }

    public static void setTextInputArea(long session, boolean available, float x, float y, float height) {
        final CocosGLSurfaceView view = mGLSurfaceView;
        if (view == null) return;
        view.mImeHandler.post(() -> {
            if (!view.isTextInputCurrent(session)) return;
            view.mHasCaret = available;
            view.mCaretX = x;
            view.mCaretY = y;
            view.mCaretHeight = height;
            if ((view.mCursorUpdateMode & InputConnection.CURSOR_UPDATE_MONITOR) != 0) view.updateTextInputCaret();
        });
    }

    public static void setTextInputSnapshot(long session, long epoch, long revision, long acknowledged, long origin,
            String text, int anchor, int focus) {
        final CocosGLSurfaceView view = mGLSurfaceView;
        if (view == null) return;
        view.mImeHandler.post(() -> {
            if (!view.isTextInputCurrent(session)) return;
            final TextInputWrapper.SnapshotResult result = view.mTextInputWrapper.setSnapshot(
                    epoch, revision, acknowledged, origin, text, anchor, focus);
            if (result == TextInputWrapper.SnapshotResult.INVALID) {
                view.dismissTextInput(CLOSE_ACTIVATION_FAILED);
                return;
            }
            if (result == TextInputWrapper.SnapshotResult.APPLIED) {
                view.restartTextInput(view.mWaitingForSnapshot);
                view.mWaitingForSnapshot = false;
            }
        });
    }

    void textInputSelectionChanged() {
        mTextInputWrapper.afterSelectionChanged();
    }

    boolean requestTextInputCursorUpdates(int mode) {
        if (!isTextInputCurrent(mTextInputSession)) return false;
        mCursorUpdateMode = mode;
        if ((mode & InputConnection.CURSOR_UPDATE_IMMEDIATE) != 0) updateTextInputCaret();
        return true;
    }

    private void updateTextInputCaret() {
        if (!isTextInputCurrent(mTextInputSession)) return;
        final InputMethodManager imm = textInputManager();
        if (imm == null) return;
        final int[] origin = new int[2];
        getLocationOnScreen(origin);
        final Matrix toScreen = new Matrix();
        toScreen.setTranslate(origin[0], origin[1]);
        final CursorAnchorInfo.Builder info = new CursorAnchorInfo.Builder().setMatrix(toScreen);
        if (mHasCaret) {
            final float density = getResources().getDisplayMetrics().density;
            final float x = mCaretX * density;
            final float top = mCaretY * density;
            final float bottom = top + mCaretHeight * density;
            final boolean visible = x >= 0 && x <= getWidth() && top < getHeight() && bottom > 0;
            info.setInsertionMarkerLocation(x, top, bottom, bottom,
                    visible ? CursorAnchorInfo.FLAG_HAS_VISIBLE_REGION : CursorAnchorInfo.FLAG_HAS_INVISIBLE_REGION);
        }
        imm.updateCursorAnchorInfo(mEditText, info.build());
    }

    private boolean isTextInputCurrent(long session) {
        return session != 0 && session == mTextInputSession && isCurrentHost() &&
                mRenderHost.isTextInputCurrent(mTextInputGeneration);
    }

    void commitTextInput(String text) {
        if (!mWaitingForSnapshot && !text.isEmpty() && isTextInputCurrent(mTextInputSession))
            nativeTextInputCommit(mTextInputSession, text);
    }

    boolean editTextInput(long epoch, long revision, long transaction, long origin,
            String previous, String current, int anchor, int focus) {
        return isTextInputCurrent(mTextInputSession) && nativeTextInputEdit(mTextInputSession,
                epoch, revision, transaction, origin, previous, current, anchor, focus);
    }

    void observeTextInputPreedit(String text, int phase, int anchor, int focus) {
        if (!mWaitingForSnapshot && isTextInputCurrent(mTextInputSession))
            nativeTextInputPreedit(mTextInputSession, text, phase, anchor, focus);
    }

    boolean deleteTextInput(int before, int after) {
        if (before == 1 && after == 0) return sendTextInputCommand(TEXT_BACKSPACE);
        if (before == 0 && after == 1) return sendTextInputCommand(TEXT_DELETE);
        return false;
    }

    boolean handleTextInputEditorAction(int action) {
        switch (action) {
            case EditorInfo.IME_ACTION_DONE: return sendTextInputCommand(TEXT_DONE);
            case EditorInfo.IME_ACTION_SEARCH: return sendTextInputCommand(TEXT_SEARCH);
            case EditorInfo.IME_ACTION_SEND: return sendTextInputCommand(TEXT_SEND);
            case EditorInfo.IME_ACTION_NEXT: return sendTextInputCommand(TEXT_NEXT);
            case EditorInfo.IME_ACTION_GO: return sendTextInputCommand(TEXT_GO);
            case EditorInfo.IME_NULL:
            case EditorInfo.IME_ACTION_NONE: return sendTextInputCommand(mTextInputMultiline ? TEXT_NEWLINE : TEXT_DONE);
            default: return false;
        }
    }

    private boolean sendTextInputCommand(int command) {
        if (command < 0 || !isTextInputCurrent(mTextInputSession)) return false;
        nativeTextInputCommand(mTextInputSession, command);
        return true;
    }

    boolean handleTextInputKey(KeyEvent event) {
        if (mTextInputWrapper.isRangeReady() && event.getKeyCode() != KeyEvent.KEYCODE_ESCAPE) return false;
        final int command = textInputCommandForKey(event);
        if (command < 0) return false;
        if (event.getAction() == KeyEvent.ACTION_DOWN) sendTextInputCommand(command);
        return true;
    }

    private int textInputCommandForKey(KeyEvent event) {
        switch (event.getKeyCode()) {
            case KeyEvent.KEYCODE_DEL: return mEditText.length() == 0 ? TEXT_BACKSPACE : -1;
            case KeyEvent.KEYCODE_FORWARD_DEL: return mEditText.length() == 0 ? TEXT_DELETE : -1;
            case KeyEvent.KEYCODE_DPAD_LEFT: return TEXT_LEFT;
            case KeyEvent.KEYCODE_DPAD_RIGHT: return TEXT_RIGHT;
            case KeyEvent.KEYCODE_DPAD_UP: return TEXT_UP;
            case KeyEvent.KEYCODE_DPAD_DOWN: return TEXT_DOWN;
            case KeyEvent.KEYCODE_MOVE_HOME: return TEXT_LINE_START;
            case KeyEvent.KEYCODE_MOVE_END: return TEXT_LINE_END;
            case KeyEvent.KEYCODE_A: return event.isCtrlPressed() ? TEXT_SELECT_ALL : -1;
            case KeyEvent.KEYCODE_ESCAPE: return TEXT_CANCEL;
            default: return -1;
        }
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
