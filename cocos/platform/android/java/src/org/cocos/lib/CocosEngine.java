/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2019-present Cocos Engine contributors (see AUTHORS.md).

https://axmol.dev/

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

import android.annotation.SuppressLint;
import android.content.pm.PackageManager;
import android.media.AudioManager;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.os.IBinder;
import android.os.ParcelFileDescriptor;
import android.os.Vibrator;
import android.preference.PreferenceManager.OnActivityResultListener;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.DisplayCutout;
import android.view.KeyCharacterMap;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.view.Window;
import android.view.WindowInsets;
import android.view.WindowManager;

import com.android.vending.expansion.zipfile.APKExpansionSupport;
import com.android.vending.expansion.zipfile.ZipResourceFile;

import com.jakewharton.processphoenix.ProcessPhoenix;

import java.io.IOException;
import java.io.File;
import java.io.FilenameFilter;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.LinkedHashSet;
import java.util.Locale;
import java.util.Map;
import java.util.Objects;
import java.util.Set;


public class CocosEngine {
    // ===========================================================
    // Constants
    // ===========================================================
    private static final String PREFS_NAME = "CocosPrefsFile";
    private static final int RUNNABLES_PER_FRAME = 5;
    private static final String TAG = CocosEngine.class.getSimpleName();

    // ===========================================================
    // Fields
    // ===========================================================
    private static AssetManager sAssetManager;
    private static CocosAccelerometer sAccelerometer = null;
    private static boolean sAccelerometerEnabled;
    private static boolean sCompassEnabled;
    private static volatile boolean sActivityVisible;
    private static String sPackageName;
    private static volatile Activity sActivity = null;
    private static volatile int[] sSafeInsets = new int[4];
    private static volatile int[] sCornerRadii = new int[4];
    private static volatile int sDPI = -1;
    private static volatile int[] sDisplayResolution = new int[2];
    private static volatile boolean sWindowVisible;
    private static volatile boolean sImeVisible;
    private static volatile ClipboardManager sClipboard;
    private static volatile boolean sScreenRound;
    private static volatile boolean sCutoutEnabled;
    private static volatile boolean sHasSoftKeys = true;
    private static volatile CocosEngineListener sCocosEngineListener;
    private static Set<OnActivityResultListener> onActivityResultListeners = new LinkedHashSet<OnActivityResultListener>();
    private static Vibrator sVibrateService = null;

    // The absolute path to the OBB if it exists, else the absolute path to the APK.
    private static String sAssetsPath = "";

    // The OBB file
    private static ZipResourceFile sOBBFile = null;

    // ===========================================================
    // Constructors
    // ===========================================================

    public static void runOnGLThread(final Runnable r) {
        final CocosGLSurfaceView view = CocosGLSurfaceView.getInstance();
        if (view == null) {
            Log.w(TAG, "runOnGLThread rejected before RenderHost creation");
            return;
        }
        view.queueEvent(r);
    }

    public static void runOnUiThread(final Runnable r) {
        final Activity activity = sActivity;
        if (activity != null) activity.runOnUiThread(() -> {
            if (sActivity == activity && !activity.isDestroyed()) r.run();
        });
    }

    public static void queueOperation(final long op, final long param) {
        runOnGLThread(new Runnable() {
            @Override
            public void run() {
                CocosEngine.nativeCall0(op, param);
            }
        });
    }

    private static boolean sInited = false;
    public static void init(final Activity activity) {
        sActivity = activity;
        sActivityVisible = false;
        sSafeInsets = new int[4];
        sCornerRadii = new int[4];
        sDisplayResolution = new int[2];
        sWindowVisible = false;
        sImeVisible = false;
        // Acquire services on the UI thread; clipboard calls themselves use Binder
        // and must not wait for a UI callback from the engine thread.
        sClipboard = (ClipboardManager) activity.getSystemService(Context.CLIPBOARD_SERVICE);
        sDPI = activity.getResources().getDisplayMetrics().densityDpi;
        sCutoutEnabled = false;
        sHasSoftKeys = computeHasSoftKeys(activity);
        sScreenRound = Build.VERSION.SDK_INT >= Build.VERSION_CODES.M
                && activity.getResources().getConfiguration().isScreenRound();
        CocosEngine.sCocosEngineListener = (CocosEngineListener)activity;
        CocosEngine.sAssetManager = activity.getAssets();
        CocosEngine.nativeSetContext((Context)activity, CocosEngine.sAssetManager);
        prepareWritableDirectorySnapshot(activity.getApplicationContext());
        BitmapHelper.setContext(activity.getApplicationContext());
        CocosEngine.sVibrateService = (Vibrator)activity.getSystemService(Context.VIBRATOR_SERVICE);
        // Sensor listeners retain their Activity; release them before rebinding.
        if (sAccelerometer != null) sAccelerometer.disable();
        sAccelerometer = null;
        if (!sInited) {

            PackageManager pm = activity.getPackageManager();
            boolean isSupportLowLatency = pm.hasSystemFeature(PackageManager.FEATURE_AUDIO_LOW_LATENCY);
            Log.d(TAG, String.format("android version is %d, isSupportLowLatency: %s", Build.VERSION.SDK_INT, isSupportLowLatency ? "true" : "false") );

            final ApplicationInfo applicationInfo = activity.getApplicationInfo();

            CocosEngine.sPackageName = applicationInfo.packageName;

            sInited = true;
        }
        refreshWindowInfo(activity);
        activity.getWindow().getDecorView().getViewTreeObserver()
                .addOnGlobalLayoutListener(() -> refreshWindowInfo(activity));
    }

    static void unbindActivity(Activity activity) {
        if (sActivity != activity) return;
        if (sAccelerometer != null) sAccelerometer.disable();
        sAccelerometer = null;
        sActivityVisible = false;
        sCocosEngineListener = null;
        sActivity = null;
        sSafeInsets = new int[4];
        sCornerRadii = new int[4];
        sDisplayResolution = new int[2];
        sWindowVisible = false;
        sImeVisible = false;
        sClipboard = null;
        sCutoutEnabled = false;
        // Native context is rebound by init before the next Activity's host starts.
    }

    // This function returns the absolute path to the OBB if it exists,
    // else it returns the absolute path to the APK.
    public static String getAssetsPath()
    {
        if (CocosEngine.sAssetsPath.equals("")) {

            String pathToOBB = Environment.getExternalStorageDirectory().getAbsolutePath() + "/Android/obb/" + CocosEngine.sPackageName;

	    	// Listing all files inside the folder (pathToOBB) where OBB files are expected to be found.
            String[] fileNames = new File(pathToOBB).list(new FilenameFilter() { // Using filter to pick up only main OBB file name.
                public boolean accept(File dir, String name) {
                    return name.startsWith("main.") && name.endsWith(".obb");  // It's possible to filter only by extension here to get path to patch OBB file also.
                }
            });

            String fullPathToOBB = "";
            if (fileNames != null && fileNames.length > 0)  // If there is at least 1 element inside the array with OBB file names, then we may think fileNames[0] will have desired main OBB file name.
                fullPathToOBB = pathToOBB + "/" + fileNames[0];  // Composing full file name for main OBB file.

            File obbFile = new File(fullPathToOBB);
            if (obbFile.exists())
                CocosEngine.sAssetsPath = fullPathToOBB;
            else
                CocosEngine.sAssetsPath = CocosEngine.sActivity.getApplicationInfo().sourceDir;
        }

        return CocosEngine.sAssetsPath;
    }

    public static ZipResourceFile getObbFile() {
        if (null == sOBBFile) {
            int versionCode = 1;
            try {
                versionCode = CocosActivity.getContext().getPackageManager().getPackageInfo(CocosEngine.getPackageName(), 0).versionCode;
            } catch (NameNotFoundException e) {
                e.printStackTrace();
            }

            try {
                sOBBFile = APKExpansionSupport.getAPKExpansionZipFile(CocosActivity.getContext(), versionCode, 0);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return sOBBFile;
    }

    public static Activity getActivity() {
        return sActivity;
    }

    public static void addOnActivityResultListener(OnActivityResultListener listener) {
        onActivityResultListeners.add(listener);
    }

    public static Set<OnActivityResultListener> getOnActivityResultListeners() {
        return onActivityResultListeners;
    }

    public static boolean isActivityVisible(){
        return sActivityVisible;
    }

    /** Nonblocking UI snapshots. Physical Surface size is owned by native RenderHost. */
    public static int[] getDisplayResolution() {
        return sDisplayResolution.clone();
    }

    public static boolean isWindowVisible() {
        return sActivity != null && sActivityVisible && sWindowVisible;
    }

    public static boolean isImeVisible() {
        return isWindowVisible() && sImeVisible;
    }

    public static void setClipboardString(String text) {
        final ClipboardManager clipboard = sClipboard;
        if (!isWindowVisible() || clipboard == null) {
            Log.w(TAG, "setClipboardString rejected without a foreground window");
            return;
        }
        try {
            clipboard.setPrimaryClip(ClipData.newPlainText("", text));
        } catch (RuntimeException e) {
            Log.w(TAG, "setClipboardString failed", e);
        }
    }

    public static String getClipboardString() {
        final ClipboardManager clipboard = sClipboard;
        if (!isWindowVisible() || clipboard == null) return "";
        try {
            // Android enforces input-focus access. Never return a stale cached copy.
            final ClipData clip = clipboard.getPrimaryClip();
            if (clip == null || clip.getItemCount() == 0) return "";
            // This API only transfers text; do not dereference clipboard content URIs.
            final CharSequence text = clip.getItemAt(0).getText();
            return text == null ? "" : text.toString();
        } catch (RuntimeException e) {
            Log.w(TAG, "getClipboardString failed", e);
            return "";
        }
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    // ===========================================================
    // Methods
    // ===========================================================

    private static native void nativeSetEditTextDialogResult(final byte[] pBytes);

    private static native void nativeSetContext(final Object pContext, final Object pAssetManager);

    private static native boolean nativeUsesExternalWritablePath();
    private static native void nativeSetDefaultWritablePath(final String path);

    // Explicit storage preparation: these Android APIs may create their directory.
    // Native FileUtils getters and reset only consume the published snapshot.
    private static void prepareWritableDirectorySnapshot(final Context context) {
        String path = "";
        if (context != null) {
            try {
                final File directory = nativeUsesExternalWritablePath()
                        ? context.getExternalFilesDir(null) : context.getFilesDir();
                if (directory != null) path = directory.getAbsolutePath();
            } catch (RuntimeException failure) {
                Log.w(TAG, "Unable to prepare the default writable directory", failure);
            }
        }
        nativeSetDefaultWritablePath(path);
    }

    // private static native void nativeSetAudioDeviceInfo(boolean isSupportLowLatency, int deviceSampleRate, int audioBufferSizeInFames);

    public static native void nativeCall0(long func, long ud);

    public static String getPackageName() {
        return CocosEngine.sPackageName;
    }
    public static String getInternalFilesDir() {
        return sActivity.getFilesDir().getAbsolutePath();
    }
    public static String getCocosPackageName() {
        return getPackageName();
    }
    public static String getCocosWritablePath() {
        return getInternalFilesDir();
    }

    public static String getExternalFilesDir() {
        return Objects.requireNonNull(sActivity.getExternalFilesDir(null)).getAbsolutePath();
    }

    public static String getCurrentLanguage() {
        return Locale.getDefault().getLanguage();
    }

    public static String getDeviceModel(){
        return Build.MODEL;
    }

    public static AssetManager getAssetManager() {
        return CocosEngine.sAssetManager;
    }

    public static void enableAccelerometer() {
        CocosEngine.sAccelerometerEnabled = true;
        CocosEngine.getAccelerometer().enableAccel();
    }

    public static void enableCompass() {
        CocosEngine.sCompassEnabled = true;
        CocosEngine.getAccelerometer().enableCompass();
    }

    public static void setAccelerometerInterval(float interval) {
        CocosEngine.getAccelerometer().setInterval(interval);
    }

    public static void disableAccelerometer() {
        CocosEngine.sAccelerometerEnabled = false;
        CocosEngine.getAccelerometer().disable();
    }

    public static void setKeepScreenOn(boolean value) {
        ((CocosActivity)sActivity).setKeepScreenOn(value);
    }

    public static void vibrate(float duration) {
        sVibrateService.vibrate((long)(duration * 1000));
    }

    public static void impactOccurred(int style) {
        ((CocosActivity)sActivity).impactOccurred(style);
    }

    public static void notificationOccurred(int type) {
        ((CocosActivity)sActivity).notificationOccurred(type);
    }

    public static void selectionChanged() {
        ((CocosActivity)sActivity).selectionChanged();
    }

 	public static String getVersion() {
 		try {
 			String version = CocosActivity.getContext().getPackageManager().getPackageInfo(CocosActivity.getContext().getPackageName(), 0).versionName;
 			return version;
 		} catch(Exception e) {
 			return "";
 		}
 	}

    public static boolean openURL(String url) {
        boolean ret = false;
        try {
            Intent i = new Intent(Intent.ACTION_VIEW);
            i.setData(Uri.parse(url));
            sActivity.startActivity(i);
            ret = true;
        } catch (Exception e) {
        }
        return ret;
    }

    public static long[] getObbAssetFileDescriptor(final String path) {
        long[] array = new long[3];
        if (CocosEngine.getObbFile() != null) {
            AssetFileDescriptor descriptor = CocosEngine.getObbFile().getAssetFileDescriptor(path);
            if (descriptor != null) {
                try {
                    ParcelFileDescriptor parcel = descriptor.getParcelFileDescriptor();
                    Method method = parcel.getClass().getMethod("getFd", new Class[] {});
                    array[0] = (Integer)method.invoke(parcel);
                    array[1] = descriptor.getStartOffset();
                    array[2] = descriptor.getLength();
                } catch (NoSuchMethodException e) {
                    Log.e(CocosEngine.TAG, "Accessing file descriptor directly from the OBB is only supported from Android 3.1 (API level 12) and above.");
                } catch (IllegalAccessException e) {
                    Log.e(CocosEngine.TAG, e.toString());
                } catch (InvocationTargetException e) {
                    Log.e(CocosEngine.TAG, e.toString());
                }
            }
        }
        return array;
    }

    public static void onResume() {
        sActivityVisible = true;
        if (CocosEngine.sAccelerometerEnabled) {
            CocosEngine.getAccelerometer().enableAccel();
        }
        if (CocosEngine.sCompassEnabled) {
            CocosEngine.getAccelerometer().enableCompass();
        }
    }

    public static void onPause() {
        sActivityVisible = false;
        sImeVisible = false;
        if (sAccelerometer != null) sAccelerometer.disable();
    }

    public static void onExit() {
        // Remove it from recent apps.
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            final Activity activity = sActivity;
            if (activity != null) runOnUiThread(() -> activity.finishAndRemoveTask());
        }
    }

    public static void terminateProcess() {
        onExit();
        android.os.Process.killProcess(android.os.Process.myPid());
    }

    public static void showDialog(final String pTitle, final String pMessage) {
        final CocosEngineListener listener = sCocosEngineListener;
        if (listener == null) throw new IllegalStateException("No Activity bound for showDialog");
        // CocosActivity dispatches the dialog through its UI handler.
        listener.showDialog(pTitle, pMessage);
    }


    public static void setEditTextDialogResult(final String pResult) {
        try {
            final byte[] bytesUTF8 = pResult.getBytes("UTF8");

            CocosEngine.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    CocosEngine.nativeSetEditTextDialogResult(bytesUTF8);
                }
            });
        } catch (UnsupportedEncodingException pUnsupportedEncodingException) {
            /* Nothing. */
        }
    }

    public static int getDPI()
    {
        return sDPI;
    }

    // ===========================================================
    // Functions for CCUserDefault
    // ===========================================================

    public static boolean getBoolForKey(String key, boolean defaultValue) {
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        try {
            return settings.getBoolean(key, defaultValue);
        }
        catch (Exception ex) {
            ex.printStackTrace();

            Map allValues = settings.getAll();
            Object value = allValues.get(key);
            if ( value instanceof String)
            {
                return  Boolean.parseBoolean(value.toString());
            }
            else if (value instanceof Integer)
            {
                int intValue = ((Integer) value).intValue();
                return (intValue !=  0) ;
            }
            else if (value instanceof Float)
            {
                float floatValue = ((Float) value).floatValue();
                return (floatValue != 0.0f);
            }
        }

        return defaultValue;
    }

    public static int getIntegerForKey(String key, int defaultValue) {
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        try {
            return settings.getInt(key, defaultValue);
        }
        catch (Exception ex) {
            ex.printStackTrace();

            Map allValues = settings.getAll();
            Object value = allValues.get(key);
            if ( value instanceof String) {
                return  Integer.parseInt(value.toString());
            }
            else if (value instanceof Float)
            {
                return ((Float) value).intValue();
            }
            else if (value instanceof Boolean)
            {
                boolean booleanValue = ((Boolean) value).booleanValue();
                if (booleanValue)
                    return 1;
            }
        }

        return defaultValue;
    }

    public static float getFloatForKey(String key, float defaultValue) {
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        try {
            return settings.getFloat(key, defaultValue);
        }
        catch (Exception ex) {
            ex.printStackTrace();

            Map allValues = settings.getAll();
            Object value = allValues.get(key);
            if ( value instanceof String) {
                return  Float.parseFloat(value.toString());
            }
            else if (value instanceof Integer)
            {
                return ((Integer) value).floatValue();
            }
            else if (value instanceof Boolean)
            {
                boolean booleanValue = ((Boolean) value).booleanValue();
                if (booleanValue)
                    return 1.0f;
            }
        }

        return defaultValue;
    }

    public static double getDoubleForKey(String key, double defaultValue) {
        // SharedPreferences doesn't support saving double value
        return getFloatForKey(key, (float) defaultValue);
    }

    public static String getStringForKey(String key, String defaultValue) {
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        try {
            return settings.getString(key, defaultValue);
        }
        catch (Exception ex) {
            ex.printStackTrace();

            return settings.getAll().get(key).toString();
        }
    }

    public static void setBoolForKey(String key, boolean value) {
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        SharedPreferences.Editor editor = settings.edit();
        editor.putBoolean(key, value);
        editor.apply();
    }

    public static void setIntegerForKey(String key, int value) {
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        SharedPreferences.Editor editor = settings.edit();
        editor.putInt(key, value);
        editor.apply();
    }

    public static void setFloatForKey(String key, float value) {
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        SharedPreferences.Editor editor = settings.edit();
        editor.putFloat(key, value);
        editor.apply();
    }

    public static void setDoubleForKey(String key, double value) {
        // SharedPreferences doesn't support recording double value
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        SharedPreferences.Editor editor = settings.edit();
        editor.putFloat(key, (float)value);
        editor.apply();
    }

    public static void setStringForKey(String key, String value) {
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        SharedPreferences.Editor editor = settings.edit();
        editor.putString(key, value);
        editor.apply();
    }

    public static void deleteValueForKey(String key) {
        SharedPreferences settings = sActivity.getSharedPreferences(CocosEngine.PREFS_NAME, 0);
        SharedPreferences.Editor editor = settings.edit();
        editor.remove(key);
        editor.apply();
    }

    public static byte[] conversionEncoding(byte[] text, String fromCharset,String newCharset)
    {
        try {
            String str = new String(text,fromCharset);
            return str.getBytes(newCharset);
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        return null;
    }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================

    public static interface CocosEngineListener {
        public void showDialog(final String pTitle, final String pMessage);
    }

    /**
     * Returns whether the screen has a round shape. Apps may choose to change styling based
     * on this property, such as the alignment or layout of text or informational icons.
     *
     * @return true if the screen is rounded, false otherwise
     */
    public static boolean isScreenRound() {
        return sScreenRound;
    }

    /**
     * Returns whether the window is always allowed to extend into the DisplayCutout areas on the short edges of the screen.
     *
     * @return true if the window in display cutout mode on the short edges of the screen, false otherwise
     */
    @SuppressLint("InlinedApi")
    public static boolean isCutoutEnabled() {
        return sCutoutEnabled;
    }

    /**
     * Returns safe insets array.
     *
     * @return array of int with safe insets values
     */
    @SuppressLint("NewApi")
    public static int[] getSafeInsets() {
        return sSafeInsets.clone();
    }

    // UI-owned snapshots: engine queries must never wait for a UI callback.
    @SuppressLint("NewApi")
    static void refreshWindowInfo(Activity activity) {
        refreshWindowInfo(activity, null);
    }

    @SuppressLint("NewApi")
    static void refreshWindowInfo(Activity activity, WindowInsets currentInsets) {
        if (activity != sActivity || android.os.Looper.myLooper() != android.os.Looper.getMainLooper()) return;
        final int[] safeInsets = new int[]{0, 0, 0, 0};
        final int[] radii = new int[4];
        sDPI = activity.getResources().getDisplayMetrics().densityDpi;
        sScreenRound = Build.VERSION.SDK_INT >= Build.VERSION_CODES.M
                && activity.getResources().getConfiguration().isScreenRound();
        sHasSoftKeys = computeHasSoftKeys(activity);
        final Window window = activity.getWindow();
        final int cutoutMode = Build.VERSION.SDK_INT >= Build.VERSION_CODES.P && window != null
                ? window.getAttributes().layoutInDisplayCutoutMode : 0;
        sCutoutEnabled = Build.VERSION.SDK_INT >= Build.VERSION_CODES.P
                && (cutoutMode == WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES
                || (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R
                && cutoutMode == WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_ALWAYS));
        final View decor = window == null ? null : window.getDecorView();
        sWindowVisible = decor != null && decor.isShown() && decor.getWindowVisibility() == View.VISIBLE;
        final Display display = decor == null ? null : decor.getDisplay();
        final DisplayMetrics displayMetrics = new DisplayMetrics();
        if (display != null) display.getRealMetrics(displayMetrics);
        sDisplayResolution = new int[]{displayMetrics.widthPixels, displayMetrics.heightPixels};
        final WindowInsets insets = currentInsets != null ? currentInsets
                : Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && decor != null ? decor.getRootWindowInsets() : null;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R && insets != null) {
            sImeVisible = insets.isVisible(WindowInsets.Type.ime());
        } else if (decor != null) {
            // Before API30 there is no public IME visibility API. Observe keyboard
            // occlusion for adjust-pan/resize windows; floating keyboards may not occlude.
            final android.graphics.Rect frame = new android.graphics.Rect();
            final int[] location = new int[2];
            decor.getWindowVisibleDisplayFrame(frame);
            decor.getLocationOnScreen(location);
            final int stableBottom = insets == null ? 0 : insets.getStableInsetBottom();
            final int occluded = location[1] + decor.getHeight() - frame.bottom - stableBottom;
            sImeVisible = !frame.isEmpty() && occluded > 100 * activity.getResources().getDisplayMetrics().density;
        } else {
            sImeVisible = false;
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R && insets != null) {
            android.graphics.Insets bars = insets.getInsets(WindowInsets.Type.systemBars() | WindowInsets.Type.displayCutout());
            safeInsets[0] = bars.bottom;
            safeInsets[1] = bars.left;
            safeInsets[2] = bars.right;
            safeInsets[3] = bars.top;
        } else if (insets != null) {
            // IME occlusion is separate from the physical window's safe area.
            safeInsets[0] = Math.min(insets.getSystemWindowInsetBottom(), insets.getStableInsetBottom());
            safeInsets[1] = insets.getSystemWindowInsetLeft();
            safeInsets[2] = insets.getSystemWindowInsetRight();
            safeInsets[3] = insets.getSystemWindowInsetTop();
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P && insets != null) {
            DisplayCutout displayCutout = insets.getDisplayCutout();
            if (displayCutout != null) {
                safeInsets[0] = Math.max(safeInsets[0], displayCutout.getSafeInsetBottom());
                safeInsets[1] = Math.max(safeInsets[1], displayCutout.getSafeInsetLeft());
                safeInsets[2] = Math.max(safeInsets[2], displayCutout.getSafeInsetRight());
                safeInsets[3] = Math.max(safeInsets[3], displayCutout.getSafeInsetTop());
            }
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S && insets != null) {
            android.view.RoundedCorner topLeft = insets.getRoundedCorner(android.view.RoundedCorner.POSITION_TOP_LEFT);
            android.view.RoundedCorner topRight = insets.getRoundedCorner(android.view.RoundedCorner.POSITION_TOP_RIGHT);
            android.view.RoundedCorner bottomLeft = insets.getRoundedCorner(android.view.RoundedCorner.POSITION_BOTTOM_LEFT);
            android.view.RoundedCorner bottomRight = insets.getRoundedCorner(android.view.RoundedCorner.POSITION_BOTTOM_RIGHT);
            int radiusTopLeft = 0;
            int radiusTopRight = 0;
            int radiusBottomLeft = 0;
            int radiusBottomRight = 0;
            if (topLeft != null) radiusTopLeft = topLeft.getRadius();
            if (topRight != null) radiusTopRight = topRight.getRadius();
            if (bottomLeft != null) radiusBottomLeft = bottomLeft.getRadius();
            if (bottomRight != null) radiusBottomRight = bottomRight.getRadius();

            int leftRadius = Math.max(radiusTopLeft, radiusBottomLeft);
            int topRadius = Math.max(radiusTopLeft, radiusTopRight);
            int rightRadius = Math.max(radiusTopRight, radiusBottomRight);
            int bottomRadius = Math.max(radiusBottomLeft, radiusBottomRight);

            radii[0] = bottomRadius;
            radii[1] = leftRadius;
            radii[2] = rightRadius;
            radii[3] = topRadius;
        }
        sSafeInsets = safeInsets;
        sCornerRadii = radii;
    }

    /** Returns the latest UI snapshot in bottom/left/right/top order, never null. */
    public static int[] getDeviceCornerRadii() {
        return sCornerRadii.clone();
    }

    /**
     * Queries about whether any physical keys exist on the
     * any keyboard attached to the device and returns <code>true</code>
     * if the device does not have physical keys
     *
     * @return Returns <code>true</code> if the device have no physical keys,
     * otherwise <code>false</code> will returned.
     */
    public static boolean hasSoftKeys() {
        return sHasSoftKeys;
    }

    private static boolean computeHasSoftKeys(Activity activity) {
        boolean hasSoftwareKeys = true;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            WindowManager wm = activity.getWindowManager();
            Display display = wm == null ? null : wm.getDefaultDisplay();
            if (display == null) return true;

            DisplayMetrics realDisplayMetrics = new DisplayMetrics();
            display.getRealMetrics(realDisplayMetrics);

            int realHeight = realDisplayMetrics.heightPixels;
            int realWidth = realDisplayMetrics.widthPixels;

            DisplayMetrics displayMetrics = new DisplayMetrics();
            display.getMetrics(displayMetrics);

            int displayHeight = displayMetrics.heightPixels;
            int displayWidth = displayMetrics.widthPixels;

            hasSoftwareKeys = (realWidth - displayWidth) > 0 ||
                    (realHeight - displayHeight) > 0;
        } else {
            boolean hasMenuKey = ViewConfiguration.get(activity).hasPermanentMenuKey();
            boolean hasBackKey = KeyCharacterMap.deviceHasKey(KeyEvent.KEYCODE_BACK);
            hasSoftwareKeys = !hasMenuKey && !hasBackKey;
        }        return hasSoftwareKeys;
    }

    public static float[] getAccelValue() {
        return CocosEngine.getAccelerometer().accelerometerValues;
    }

    public static float[] getCompassValue() {
        return CocosEngine.getAccelerometer().compassFieldValues;
    }

    public static int getSDKVersion() {
        return Build.VERSION.SDK_INT;
    }

    public static void restartProcess() {
        ProcessPhoenix.triggerRebirth(sActivity);
    }

    private static CocosAccelerometer getAccelerometer() {
        if (null == sAccelerometer)
            CocosEngine.sAccelerometer = new CocosAccelerometer(sActivity);

        return sAccelerometer;
    }

    public static String[] getAssetsList(String path) {
        try {
            String basePath;
            if (!path.isEmpty()) {
                basePath = path + "/";
            } else {
                basePath = path;
            }

            AssetManager assetManager = getAssetManager();
            String[] list = assetManager.list(path);
            for (int i = 0; i < list.length; i++) {
                try {
                    list[i] = basePath + list[i];
                    java.io.InputStream stream = assetManager.open(list[i]);
                    stream.close(); // if we got to here, then it is a file
                } catch (IOException e) {
                    list[i] += "/";
                }
            }
            return list;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}
