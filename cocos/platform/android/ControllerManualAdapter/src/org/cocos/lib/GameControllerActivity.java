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

import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.Set;

import org.cocos.lib.GameControllerDelegate.ControllerEventListener;
import org.cocos.lib.inputmanagercompat.InputManagerCompat;
import org.cocos.lib.inputmanagercompat.InputManagerCompat.InputDeviceListener;
import org.cocos.lib.CocosActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.util.Log;

public abstract class GameControllerActivity extends CocosActivity implements InputDeviceListener {
    // ===========================================================
    // Constants
    // ===========================================================

    private final static String TAG = GameControllerActivity.class.getSimpleName();

    public static final int DRIVERTYPE_NIBIRU = 0;
    public static final int DRIVERTYPE_MOGA = 1;
    public static final int DRIVERTYPE_OUYA = 2;
    public static final int DRIVERTYPE_STANDARD = 3;
    public static final int DRIVERTYPE_UNKNOWN = 4;
    
    // ===========================================================
    // Fields
    // ===========================================================
    // Only driver choices survive recreation; Activity/SDK instances never do.
    private static final Set<Integer> requestedDrivers = new LinkedHashSet<>();
    private final Handler mControllerHandler = new Handler(Looper.getMainLooper());
    private GameControllerAdapter.Source mControllerSource;
    private InputManagerCompat mInputManager = null;
    
    protected GameControllerHelper mControllerHelper = null;
    
    protected GameControllerDelegate mControllerNibiru = null;
    protected GameControllerDelegate mControllerMoga = null;
    protected GameControllerDelegate mControllerOuya = null;
    
    public void connectController(int driveType){
        if (Looper.myLooper() != Looper.getMainLooper()) {
            mControllerHandler.post(() -> connectController(driveType));
            return;
        }
        if (mControllerSource == null || !mControllerSource.isCurrent()) return;
        try {
            
            ClassLoader loader = getClassLoader();
            Class<?> controllerDelegate = null;
            if (driveType == DRIVERTYPE_MOGA) {
                if (mControllerMoga != null) {
                    return;
                }
                controllerDelegate = loader.loadClass("org.cocos.lib.GameControllerMoga");
            } else if (driveType == DRIVERTYPE_NIBIRU) {
                if (mControllerNibiru != null) {
                    return;
                }
                controllerDelegate = loader.loadClass("org.cocos.lib.GameControllerNibiru");
            } else if (driveType == DRIVERTYPE_OUYA) {
                if (mControllerOuya != null) {
                    return;
                }
                controllerDelegate = loader.loadClass("org.cocos.lib.GameControllerOuya");
            } else return;
            
            GameControllerDelegate instance = (GameControllerDelegate) controllerDelegate.getDeclaredConstructor().newInstance();
            setGameControllerInstance(instance, driveType);
        }
        catch (Exception | LinkageError e) {
            Log.e(TAG, "Cannot bind controller driver=" + driveType, e);
        }
    }
    
    public void setGameControllerInstance(GameControllerDelegate controllerDelegate, int driveType) {
        if (Looper.myLooper() != Looper.getMainLooper()) {
            mControllerHandler.post(() -> setGameControllerInstance(controllerDelegate, driveType));
            return;
        }
        if (mControllerSource == null || !mControllerSource.isCurrent() || controllerDelegate == null) return;
        final GameControllerDelegate previous = getGameControllerDelegate(driveType);
        if (previous == controllerDelegate) return;
        if (previous != null) {
            previous.setControllerEventListener(null);
            previous.onPause();
            previous.onDestroy();
        }
        if (driveType == DRIVERTYPE_NIBIRU) {
            mControllerNibiru = controllerDelegate;
        }else if (driveType == DRIVERTYPE_MOGA) {
            mControllerMoga = controllerDelegate;
        }
        else if (driveType == DRIVERTYPE_OUYA) {
            mControllerOuya = controllerDelegate;
        } else return;
        requestedDrivers.add(driveType);
        controllerDelegate.setControllerEventListener(mControllerEventListener);
        controllerDelegate.onCreate(this);
        if (mControllerSource.isResumed()) controllerDelegate.onResume();
    }
    
    public GameControllerDelegate getGameControllerDelegate(int driveType){
        if (driveType == DRIVERTYPE_NIBIRU) {
            return mControllerNibiru;
        }else if (driveType == DRIVERTYPE_MOGA) {
            return mControllerMoga;
        }
        else if (driveType == DRIVERTYPE_OUYA) {
            return mControllerOuya;
        }
        
        return null;
    }
    
    ControllerEventListener mControllerEventListener;
    
    // ===========================================================
    // Constructors
    // ===========================================================
    
    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getGLSurfaceView() == null) return; // Ignored non-root launcher Activity.
        mControllerSource = new GameControllerAdapter.Source(getGLSurfaceView());
        mControllerEventListener = mControllerSource;
        mControllerHelper = new GameControllerHelper(this);
        mInputManager = InputManagerCompat.Factory.getInputManager(this);
        mInputManager.registerInputDeviceListener(this, mControllerHandler);
        
        if (mControllerNibiru != null) {
            mControllerNibiru.setControllerEventListener(mControllerEventListener);
            mControllerNibiru.onCreate(this);
        }
        if (mControllerMoga != null) {
            mControllerMoga.setControllerEventListener(mControllerEventListener);
            mControllerMoga.onCreate(this);
        }
        if (mControllerOuya != null) {
            mControllerOuya.setControllerEventListener(mControllerEventListener);
            mControllerOuya.onCreate(this);
        }
        for (int driver : new ArrayList<>(requestedDrivers)) connectController(driver);
    }
    
    // ===========================================================
    // Getter & Setter
    // ===========================================================

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        if (mControllerSource == null || !mControllerSource.isResumed()) return super.dispatchKeyEvent(event);
        boolean handled = false; 
        if (mControllerNibiru != null) {
            handled |= mControllerNibiru.dispatchKeyEvent(event);
        }
        if (handled == false && mControllerMoga != null) {
            handled |= mControllerMoga.dispatchKeyEvent(event);
        }
        if (handled == false && mControllerOuya != null) {
            handled |= mControllerOuya.dispatchKeyEvent(event);
        }
        
        if (handled == false) {
            handled |= mControllerHelper.dispatchKeyEvent(event);
        }
        
        return handled || super.dispatchKeyEvent(event);
    }
    
    @Override
    public boolean dispatchGenericMotionEvent(MotionEvent event) {
        if (mControllerSource == null || !mControllerSource.isResumed()) return super.dispatchGenericMotionEvent(event);
        if (mInputManager != null) mInputManager.onGenericMotionEvent(event);
        boolean handled = false;
        if (mControllerNibiru != null) {
            handled |= mControllerNibiru.dispatchGenericMotionEvent(event);
        }
        if (handled == false && mControllerMoga != null) {
            handled |= mControllerMoga.dispatchGenericMotionEvent(event);
        }
        if (handled == false && mControllerOuya != null) {
            handled |= mControllerOuya.dispatchGenericMotionEvent(event);
        }
        
        if (handled == false) {
            handled |= mControllerHelper.dispatchGenericMotionEvent(event);
        }
        
        return handled || super.dispatchGenericMotionEvent(event);
    }
    
    @Override
    public void onInputDeviceAdded(int deviceId) {  
        Log.d(TAG,"onInputDeviceAdded:" + deviceId);
        
        if (mControllerSource != null && mControllerSource.isCurrent()) mControllerHelper.onInputDeviceAdded(deviceId);
    }
    /*
     * This is an unusual case. Input devices don't typically change, but they
     * certainly can --- for example a device may have different modes. We use
     * this to make sure that the ship has an up-to-date InputDevice.
     * 
     * @see
     * com.example.inputmanagercompat.InputManagerCompat.InputDeviceListener
     * #onInputDeviceChanged(int)
     */
    @Override
    public void onInputDeviceChanged(int deviceId) {
        Log.w(TAG,"onInputDeviceChanged:" + deviceId);
        if (mControllerSource != null && mControllerSource.isCurrent()) mControllerHelper.onInputDeviceChanged(deviceId);
    }
    
    /*
     * Remove any ship associated with the ID.
     * 
     * @see
     * com.example.inputmanagercompat.InputManagerCompat.InputDeviceListener
     * #onInputDeviceRemoved(int)
     */
    @Override
    public void onInputDeviceRemoved(int deviceId) {
        Log.d(TAG,"onInputDeviceRemoved:" + deviceId);
        
        if (mControllerSource != null && mControllerSource.isCurrent()) mControllerHelper.onInputDeviceRemoved(deviceId);
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (mControllerSource == null || !mControllerSource.isCurrent()) return;
        mControllerSource.setResumed(true);
        mInputManager.onResume();
        
        if (mControllerNibiru != null) {
            mControllerNibiru.onResume();
        }
        if (mControllerMoga != null) {
            mControllerMoga.onResume();
        }
        if (mControllerOuya != null) {
            mControllerOuya.onResume();
        }
        
        mControllerHelper.onResume();
    }
    
    @Override
    protected void onPause() {
        if (mControllerSource != null) mControllerSource.setResumed(false);
        if (mInputManager != null) mInputManager.onPause();
        if (mControllerHelper != null) mControllerHelper.resetInputState();
        if (mControllerNibiru != null) {
            mControllerNibiru.onPause();
        }
        if (mControllerMoga != null) {
            mControllerMoga.onPause();
        }
        if (mControllerOuya != null) {
            mControllerOuya.onPause();
        }
        
        super.onPause();
    }
    
    @Override
    protected void onDestroy() {
        final boolean current = mControllerSource != null && mControllerSource.isCurrent();
        if (mControllerSource != null) mControllerSource.invalidate();
        mControllerHandler.removeCallbacksAndMessages(null);
        if (mInputManager != null) {
            mInputManager.onPause();
            mInputManager.unregisterInputDeviceListener(this);
            mInputManager = null;
        }
        if (mControllerNibiru != null) {
            mControllerNibiru.setControllerEventListener(null);
            mControllerNibiru.onDestroy();
        }
        if (mControllerMoga != null) {
            mControllerMoga.setControllerEventListener(null);
            mControllerMoga.onDestroy();
        }
        if (mControllerOuya != null) {
            mControllerOuya.setControllerEventListener(null);
            mControllerOuya.onDestroy();
        }
        mControllerNibiru = null;
        mControllerMoga = null;
        mControllerOuya = null;
        mControllerEventListener = null;
        if (current && isFinishing() && mControllerHelper != null) mControllerHelper.mGameController.clear();
        mControllerHelper = null;
        if (current && isFinishing()) requestedDrivers.clear();
        super.onDestroy();
    }

}
