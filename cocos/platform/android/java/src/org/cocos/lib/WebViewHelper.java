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

import android.app.Activity;
import android.content.MutableContextWrapper;
import android.graphics.Color;
import android.os.Looper;
import android.util.SparseArray;
import android.view.View;
import android.widget.FrameLayout;
import android.webkit.WebSettings;

import java.util.concurrent.Callable;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.atomic.AtomicInteger;


public class WebViewHelper {
    private static final String TAG = WebViewHelper.class.getSimpleName();
    private static volatile CocosActivity sCocosActivity;
    private static FrameLayout sLayout;
    private static final CocosUiBinding uiBinding = new CocosUiBinding();

    private static final SparseArray<CocosWebView> webViews = new SparseArray<>();
    private static final AtomicInteger viewTag = new AtomicInteger();
    private static final ConcurrentHashMap<Integer, Snapshot> snapshots = new ConcurrentHashMap<>();

    private static final class Snapshot {
        volatile float opacity = 1;
        volatile boolean back;
        volatile boolean forward;
    }

    public WebViewHelper(FrameLayout layout) {
        if (sCocosActivity != null) unbind(sCocosActivity, true);
        sLayout = layout;
        sCocosActivity = (CocosActivity) layout.getContext();
        uiBinding.bind(sCocosActivity);
        for (int i = 0; i < webViews.size(); i++) {
            CocosWebView view = webViews.valueAt(i);
            if (view.getParent() instanceof android.view.ViewGroup)
                ((android.view.ViewGroup) view.getParent()).removeView(view);
            ((MutableContextWrapper) view.getContext()).setBaseContext(sCocosActivity);
            view.bindRenderView(sCocosActivity.getGLSurfaceView());
            sLayout.addView(view);
            refreshSnapshot(webViews.keyAt(i), view);
        }
    }

    static void unbind(Activity activity, boolean retain) {
        if (sCocosActivity != activity) return;
        uiBinding.unbind(activity);
        sCocosActivity = null;
        for (int i = 0; i < webViews.size(); i++) {
            CocosWebView view = webViews.valueAt(i);
            view.bindRenderView(null);
            view.onPause();
            if (view.getParent() instanceof android.view.ViewGroup)
                ((android.view.ViewGroup) view.getParent()).removeView(view);
            ((MutableContextWrapper) view.getContext()).setBaseContext(activity.getApplicationContext());
            if (!retain) view.destroy();
        }
        if (!retain) {
            webViews.clear();
            snapshots.clear();
        }
        sLayout = null;
    }

    static void setResumed(Activity activity, boolean resumed) {
        if (sCocosActivity != activity) return;
        for (int i = 0; i < webViews.size(); i++) {
            if (resumed) webViews.valueAt(i).onResume();
            else webViews.valueAt(i).onPause();
        }
    }

    static boolean isViewValid(int index) {
        return snapshots.containsKey(index);
    }

    private static boolean runOnUiThread(Runnable task) {
        return uiBinding.post(task);
    }

    static void refreshSnapshot(int index, CocosWebView view) {
        final Snapshot snapshot = snapshots.get(index);
        if (snapshot != null && webViews.get(index) == view) {
            snapshot.back = view.canGoBack();
            snapshot.forward = view.canGoForward();
        }
    }

    private static native boolean shouldStartLoading(int index, String message);

    public static boolean _shouldStartLoading(int index, String message) {
        CocosRenderHost.requireEngineThread();
        return !shouldStartLoading(index, message);
    }

    private static native void didFinishLoading(int index, String message);

    public static void _didFinishLoading(int index, String message) {
        didFinishLoading(index, message);
    }

    private static native void didFailLoading(int index, String message);

    public static void _didFailLoading(int index, String message) {
        didFailLoading(index, message);
    }

    private static native void onJsCallback(int index, String message);

    public static void _onJsCallback(int index, String message) {
        onJsCallback(index, message);
    }

    public static int createWebView() {
        final int index = viewTag.getAndIncrement();
        snapshots.put(index, new Snapshot());
        if (!runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = new CocosWebView(new MutableContextWrapper(sCocosActivity), index);
                webView.bindRenderView(sCocosActivity.getGLSurfaceView());
                FrameLayout.LayoutParams lParams = new FrameLayout.LayoutParams(
                        FrameLayout.LayoutParams.WRAP_CONTENT,
                        FrameLayout.LayoutParams.WRAP_CONTENT);
                sLayout.addView(webView, lParams);

                webViews.put(index, webView);
                if (!CocosEngine.isActivityVisible()) webView.onPause();
            }
        })) {
            snapshots.remove(index);
            return -1;
        }
        return index;
    }

    public static void removeWebView(final int index) {
        snapshots.remove(index);
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webViews.remove(index);
                    sLayout.removeView(webView);
                    webView.bindRenderView(null);
                    webView.destroy();
                }
            }
        });
    }

    public static void setVisible(final int index, final boolean visible) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.setVisibility(visible ? View.VISIBLE : View.GONE);
                }
            }
        });
    }

    public static void setBackgroundTransparent(final int index) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.setBackgroundColor(Color.TRANSPARENT);
                }
            }
        });
    }

    public static void setOpacityWebView(final int index, final float opacity) {
        final Snapshot snapshot = snapshots.get(index);
        final boolean accepted = runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.setAlpha(opacity);
                }
            }
        });
        if (accepted && snapshot != null) snapshot.opacity = opacity;
    }


    public static float getOpacityWebView(final int index) {
        final Snapshot snapshot = snapshots.get(index);
        return snapshot == null ? 1 : snapshot.opacity;
    }

    public static void setWebViewRect(final int index, final int left, final int top, final int maxWidth, final int maxHeight) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.setWebViewRect(left, top, maxWidth, maxHeight);
                }
            }
        });
    }

    public static void setJavascriptInterfaceScheme(final int index, final String scheme) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.setJavascriptInterfaceScheme(scheme);
                }
            }
        });
    }

    public static void loadData(final int index, final String data, final String mimeType, final String encoding, final String baseURL) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.loadDataWithBaseURL(baseURL, data, mimeType, encoding, null);
                }
            }
        });
    }

    public static void loadHTMLString(final int index, final String data, final String baseUrl) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.loadDataWithBaseURL(baseUrl, data, null, null, null);
                }
            }
        });
    }

    public static void loadUrl(final int index, final String url, final boolean cleanCachedData) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.getSettings().setCacheMode(cleanCachedData ? WebSettings.LOAD_NO_CACHE
                                                                       : WebSettings.LOAD_DEFAULT);
                    webView.loadUrl(url);
                }
            }
        });
    }

    public static void loadFile(final int index, final String filePath) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.loadUrl(filePath);
                }
            }
        });
    }

    public static void stopLoading(final int index) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.stopLoading();
                }
            }
        });

    }

    public static void reload(final int index) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.reload();
                }
            }
        });
    }

    public static <T> T callInMainThread(Callable<T> call) throws ExecutionException, InterruptedException {
        // Kept for Java callers, but never create an engine -> UI wait edge.
        if (Looper.myLooper() != Looper.getMainLooper())
            throw new ExecutionException(new IllegalStateException("Use UI snapshots or asynchronous UI posts"));
        try {
            return call.call();
        } catch (Exception e) {
            throw new ExecutionException(e);
        }
    }

    public static boolean canGoBack(final int index) {
        // Last UI-published history; never block the engine for a fresher answer.
        final Snapshot snapshot = snapshots.get(index);
        return snapshot != null && snapshot.back;
    }

    public static boolean canGoForward(final int index) {
        final Snapshot snapshot = snapshots.get(index);
        return snapshot != null && snapshot.forward;
    }

    public static void goBack(final int index) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.goBack();
                }
            }
        });
    }

    public static void goForward(final int index) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.goForward();
                }
            }
        });
    }

    public static void evaluateJS(final int index, final String js) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.loadUrl("javascript:" + js);
                }
            }
        });
    }

    public static void setScalesPageToFit(final int index, final boolean scalesPageToFit) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                CocosWebView webView = webViews.get(index);
                if (webView != null) {
                    webView.setScalesPageToFit(scalesPageToFit);
                }
            }
        });
    }
}
