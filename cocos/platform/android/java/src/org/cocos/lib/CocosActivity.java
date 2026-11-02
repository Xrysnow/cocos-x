/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
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
import android.app.KeyguardManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Message;
import android.os.PowerManager;
import android.preference.PreferenceManager.OnActivityResultListener;
import android.util.Log;
import android.view.HapticFeedbackConstants;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;

import org.cocos.lib.CocosEngine.CocosEngineListener;


public abstract class CocosActivity extends Activity implements CocosEngineListener {
    // ===========================================================
    // Constants
    // ===========================================================

    private final static String TAG = CocosActivity.class.getSimpleName();

    // ===========================================================
    // Fields
    // ===========================================================

    private CocosGLSurfaceView mGLSurfaceView = null;
    private CocosHandler mHandler = null;
    protected static volatile CocosActivity sContext = null;
    private WebViewHelper mWebViewHelper = null;
    private EditBoxHelper mEditBoxHelper = null;
    private boolean showVirtualButton = false;

    public CocosGLSurfaceView getGLSurfaceView(){
        return  mGLSurfaceView;
    }

    public static Context getContext() {
        return sContext;
    }

    public void setKeepScreenOn(boolean value) {
        final boolean newValue = value;
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (sContext == CocosActivity.this && mGLSurfaceView != null)
                    mGLSurfaceView.setKeepScreenOn(newValue);
            }
        });
    }

    public void impactOccurred(int style) {
        int feedback = HapticFeedbackConstants.VIRTUAL_KEY;
        performHapticFeedback(feedback);
    }

    public void notificationOccurred(int type) {
        int feedback;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            switch (type) {
                case 1:
                case 2:
                    feedback = HapticFeedbackConstants.REJECT;
                    break;
                default:
                    feedback = HapticFeedbackConstants.CONFIRM;
                    break;
            }
        } else {
            feedback = HapticFeedbackConstants.VIRTUAL_KEY;
        }
        performHapticFeedback(feedback);
    }

    public void selectionChanged() {
        int feedback;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            feedback = HapticFeedbackConstants.CLOCK_TICK;
        } else {
            feedback = HapticFeedbackConstants.VIRTUAL_KEY;
        }
        performHapticFeedback(feedback);
    }

    protected void performHapticFeedback(int feedback) {
        CocosEngine.runOnUiThread(() -> {
            if (sContext == this) getWindow().getDecorView().performHapticFeedback(feedback);
        });
    }

    public void setEnableVirtualButton(boolean value) {
        this.showVirtualButton = value;
    }

    protected void onLoadNativeLibraries() {
        final ApplicationInfo ai;
        try {
            ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
        } catch (PackageManager.NameNotFoundException e) {
            throw new IllegalStateException("Cannot read native library metadata for " + getPackageName(), e);
        }
        final String libName = ai.metaData == null ? null : ai.metaData.getString("android.app.lib_name");
        if (libName == null || libName.isEmpty()) {
            throw new IllegalStateException("Missing android.app.lib_name in application metadata");
        }
        // The platform loader resolves DT_NEEDED, including optional modules
        // selected by the native build. A load failure must stop initialization.
        System.loadLibrary(libName);
    }

    // ===========================================================
    // Constructors
    // ===========================================================

    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        Log.i(TAG, "onCreate()");
        super.onCreate(savedInstanceState);

        // Workaround in https://stackoverflow.com/questions/16283079/re-launch-of-activity-on-home-button-but-only-the-first-time/16447508
        if (!isTaskRoot()) {
            // Android launched another instance of the root activity into an existing task
            //  so just quietly finish and go away, dropping the user back into the activity
            //  at the top of the stack (ie: the last state of this task)
            finish();
            Log.w(TAG, "[Workaround] Ignore the activity started from icon!");
            return;
        }

        this.hideVirtualButton();

        onLoadNativeLibraries();

        sContext = this;
        this.mHandler = new CocosHandler(this);

        CocosEngine.init(this);

        this.init();

        if(mWebViewHelper == null){
            mWebViewHelper = new WebViewHelper(mFrameLayout);
        }

        if(mEditBoxHelper == null){
            mEditBoxHelper = new EditBoxHelper(mFrameLayout);
        }

        Window window = this.getWindow();
        window.setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_PAN);

        // Audio configuration
        this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    protected void onStart() {
        Log.i(TAG, "onStart()");
        super.onStart();

    }

    @Override
    protected void onResume() {
    	Log.i(TAG, "onResume()");
        super.onResume();
        if (sContext != this) return;

        hideVirtualButton();
        CocosEngine.onResume();
        if (mGLSurfaceView != null) mGLSurfaceView.handleOnResume();
        if (mWebViewHelper != null) WebViewHelper.setResumed(this, true);
        CocosEngine.refreshWindowInfo(this);
    }

    @Override
    protected void onPause() {
    	Log.i(TAG, "onPause()");

        if (mEditBoxHelper != null) EditBoxHelper.pause(this);
        if (mWebViewHelper != null) WebViewHelper.setResumed(this, false);
        if (mGLSurfaceView != null) mGLSurfaceView.handleOnPause();
        if (sContext == this) CocosEngine.onPause();

        super.onPause();
    }

    @Override
    protected void onStop() {
        Log.i(TAG, "onStop()");

        if (mGLSurfaceView != null) mGLSurfaceView.waitForPauseToComplete();

        super.onStop();
    }

    @Override
    protected void onRestart() {
        Log.i(TAG, "onRestart()");
        super.onRestart();
    }

    @Override
    protected void onDestroy() {
        Log.i(TAG, "onDestroy()");
        if (mHandler != null) mHandler.removeCallbacksAndMessages(null);
        if (mWebViewHelper != null) WebViewHelper.unbind(this, !isFinishing());
        if (mEditBoxHelper != null) EditBoxHelper.unbind(this, !isFinishing());
        if (mGLSurfaceView != null) mGLSurfaceView.closeRenderHost(isFinishing());
        CocosEngine.unbindActivity(this);
        if (sContext == this) sContext = null;
        super.onDestroy();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        Log.i(TAG, "onWindowFocusChanged() hasFocus=" + hasFocus);
        super.onWindowFocusChanged(hasFocus);
        if (mGLSurfaceView != null) mGLSurfaceView.handleWindowFocusChanged(hasFocus);
        if (hasFocus) CocosEngine.refreshWindowInfo(this);
    }

    @Override
    public void showDialog(final String pTitle, final String pMessage) {
        if (mHandler == null || sContext != this) return;
        Message msg = new Message();
        msg.what = CocosHandler.HANDLER_SHOW_DIALOG;
        msg.obj = new CocosHandler.DialogMessage(pTitle, pMessage);
        this.mHandler.sendMessage(msg);
    }

    @Deprecated
    public void runOnGLThread(final Runnable runnable) {
        CocosEngine.runOnGLThread(runnable);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        for (OnActivityResultListener listener : CocosEngine.getOnActivityResultListeners()) {
            listener.onActivityResult(requestCode, resultCode, data);
        }

        super.onActivityResult(requestCode, resultCode, data);
    }


    protected ResizeLayout mFrameLayout = null;
    // ===========================================================
    // Methods
    // ===========================================================
    public void init() {

        // FrameLayout
        ViewGroup.LayoutParams framelayout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.MATCH_PARENT);

        mFrameLayout = new ResizeLayout(this);

        mFrameLayout.setLayoutParams(framelayout_params);

        // CocosEditBox layout
        ViewGroup.LayoutParams edittext_layout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.WRAP_CONTENT);
        CocosEditBox edittext = new CocosEditBox(this);
        edittext.setLayoutParams(edittext_layout_params);
        edittext.setVisibility(View.GONE);

        mFrameLayout.addView(edittext);

        // CocosGLSurfaceView
        this.mGLSurfaceView = this.onCreateView();

        // ...add to FrameLayout
        mFrameLayout.addView(this.mGLSurfaceView);

        this.mGLSurfaceView.setRenderer(new CocosRenderer());
        this.mGLSurfaceView.setEditText(edittext);
        mGLSurfaceView.setOnApplyWindowInsetsListener((view, insets) -> {
            CocosEngine.refreshWindowInfo(this, insets);
            return insets;
        });
        mFrameLayout.addOnLayoutChangeListener((view, l, t, r, b, oldL, oldT, oldR, oldB) ->
                CocosEngine.refreshWindowInfo(this));

        // Set framelayout as the content view
        setContentView(mFrameLayout);
    }


    public CocosGLSurfaceView onCreateView() {
        return new CocosGLSurfaceView(this);
    }

    protected void hideVirtualButton() {
        if (showVirtualButton) {
            return;
        }

        if (Build.VERSION.SDK_INT >= 19) {
            // use reflection to remove dependence of API level

            Class viewClass = View.class;

            try {
                final int SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION = ReflectionHelper.<Integer>getConstantValue(viewClass, "SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION");
                final int SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN = ReflectionHelper.<Integer>getConstantValue(viewClass, "SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN");
                final int SYSTEM_UI_FLAG_HIDE_NAVIGATION = ReflectionHelper.<Integer>getConstantValue(viewClass, "SYSTEM_UI_FLAG_HIDE_NAVIGATION");
                final int SYSTEM_UI_FLAG_FULLSCREEN = ReflectionHelper.<Integer>getConstantValue(viewClass, "SYSTEM_UI_FLAG_FULLSCREEN");
                final int SYSTEM_UI_FLAG_IMMERSIVE_STICKY = ReflectionHelper.<Integer>getConstantValue(viewClass, "SYSTEM_UI_FLAG_IMMERSIVE_STICKY");
                final int SYSTEM_UI_FLAG_LAYOUT_STABLE = ReflectionHelper.<Integer>getConstantValue(viewClass, "SYSTEM_UI_FLAG_LAYOUT_STABLE");

                // getWindow().getDecorView().setSystemUiVisibility();
                final Object[] parameters = new Object[]{SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        | SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
                        | SYSTEM_UI_FLAG_FULLSCREEN // hide status bar
                        | SYSTEM_UI_FLAG_IMMERSIVE_STICKY};
                ReflectionHelper.<Void>invokeInstanceMethod(getWindow().getDecorView(),
                        "setSystemUiVisibility",
                        new Class[]{Integer.TYPE},
                        parameters);
            } catch (NullPointerException e) {
                Log.e(TAG, "hideVirtualButton", e);
            }
        }
    }

   private static boolean isAndroidEmulator() {
      String model = Build.MODEL;
      Log.d(TAG, "model=" + model);
      String product = Build.PRODUCT;
      Log.d(TAG, "product=" + product);
      boolean isEmulator = false;
      if (product != null) {
         isEmulator = product.equals("sdk") || product.contains("_sdk") || product.contains("sdk_");
      }
      Log.d(TAG, "isEmulator=" + isEmulator);
      return isEmulator;
   }

    private static boolean isDeviceLocked() {
        KeyguardManager keyguardManager = (KeyguardManager)getContext().getSystemService(Context.KEYGUARD_SERVICE);
        boolean locked = keyguardManager.inKeyguardRestrictedInputMode();
        return locked;
    }

    private static boolean isDeviceAsleep() {
        PowerManager powerManager = (PowerManager)getContext().getSystemService(Context.POWER_SERVICE);
        if(powerManager == null) {
            return false;
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT_WATCH) {
            return !powerManager.isInteractive();
        } else {
            return !powerManager.isScreenOn();
        }
    }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================

}
