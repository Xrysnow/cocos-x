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

import android.annotation.SuppressLint;
import android.content.Context;
import android.util.Log;
import android.view.Gravity;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.FrameLayout;

import java.lang.reflect.Method;
import java.net.URI;

public class CocosWebView extends WebView {
    private static final String TAG = WebViewHelper.class.getSimpleName();

    private int mViewTag;
    private String mJSScheme;
    private CocosGLSurfaceView mRenderView;
    private volatile long mBinding;

    public CocosWebView(Context context) {
        this(context, -1);
    }

    @SuppressLint("SetJavaScriptEnabled")
    public CocosWebView(Context context, int viewTag) {
        super(context);
        this.mViewTag = viewTag;
        this.mJSScheme = "";

        this.setFocusable(true);
        this.setFocusableInTouchMode(true);

        this.getSettings().setSupportZoom(false);

        this.getSettings().setDomStorageEnabled(true);
        this.getSettings().setJavaScriptEnabled(true);

        // `searchBoxJavaBridge_` has big security risk. http://jvn.jp/en/jp/JVN53768697
        try {
            Method method = this.getClass().getMethod("removeJavascriptInterface", new Class[]{String.class});
            method.invoke(this, "searchBoxJavaBridge_");
        } catch (Exception e) {
            Log.d(TAG, "This API level do not support `removeJavascriptInterface`");
        }

        this.setWebViewClient(new CocosWebViewClient());
        this.setWebChromeClient(new WebChromeClient());
    }

    public void setJavascriptInterfaceScheme(String scheme) {
        this.mJSScheme = scheme != null ? scheme : "";
    }

    void bindRenderView(CocosGLSurfaceView view) {
        mBinding++;
        mRenderView = view;
    }

    private void queueCallback(Runnable callback) {
        final CocosGLSurfaceView view = mRenderView;
        final long binding = mBinding;
        if (view == null || !view.isCurrentHost()) return;
        view.queueEvent(() -> {
            if (binding == mBinding && WebViewHelper.isViewValid(mViewTag)) callback.run();
        });
    }

    public void setScalesPageToFit(boolean scalesPageToFit) {
        this.getSettings().setSupportZoom(scalesPageToFit);
    }

    class CocosWebViewClient extends WebViewClient {
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, final String urlString) {
            final CocosGLSurfaceView renderView = mRenderView;
            if (renderView == null || !renderView.isCurrentHost()) return true;

            try {
                URI uri = URI.create(urlString);
                if (mJSScheme.equals(uri.getScheme())) {
                    queueCallback(new Runnable() {
                        @Override
                        public void run() {
                            WebViewHelper._onJsCallback(mViewTag, urlString);
                        }
                    });
                    return true;
                }
            } catch (Exception e) {
                Log.d(TAG, "Failed to create URI from url");
            }

            // WebView requires a synchronous veto. This is the sole UI -> engine
            // decision protocol: no frame/startup dependency, no engine -> UI wait,
            // and stale/uninitialized sessions or callback failures cancel the load.
            final long binding = mBinding;
            return renderView.decideNavigation(() -> binding != mBinding || !WebViewHelper.isViewValid(mViewTag)
                    || WebViewHelper._shouldStartLoading(mViewTag, urlString));
        }

        @Override
        public void doUpdateVisitedHistory(WebView view, String url, boolean isReload) {
            super.doUpdateVisitedHistory(view, url, isReload);
            WebViewHelper.refreshSnapshot(mViewTag, CocosWebView.this);
        }

        @Override
        public void onPageFinished(WebView view, final String url) {
            super.onPageFinished(view, url);
            WebViewHelper.refreshSnapshot(mViewTag, CocosWebView.this);
            queueCallback(new Runnable() {
                @Override
                public void run() {
                    WebViewHelper._didFinishLoading(mViewTag, url);
                }
            });
        }

        @Override
        public void onReceivedError(WebView view, int errorCode, String description, final String failingUrl) {
            super.onReceivedError(view, errorCode, description, failingUrl);
            WebViewHelper.refreshSnapshot(mViewTag, CocosWebView.this);
            queueCallback(new Runnable() {
                @Override
                public void run() {
                    WebViewHelper._didFailLoading(mViewTag, failingUrl);
                }
            });
        }
    }

    public void setWebViewRect(int left, int top, int maxWidth, int maxHeight) {
        FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                FrameLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.leftMargin = left;
        layoutParams.topMargin = top;
        layoutParams.width = maxWidth;
        layoutParams.height = maxHeight;
        layoutParams.gravity = Gravity.TOP | Gravity.LEFT;
        this.setLayoutParams(layoutParams);
    }
}
