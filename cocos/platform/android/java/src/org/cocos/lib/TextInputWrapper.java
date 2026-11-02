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

import android.text.Editable;
import android.text.TextWatcher;
import android.view.KeyEvent;
import android.view.inputmethod.BaseInputConnection;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputConnection;
import android.view.inputmethod.InputConnectionWrapper;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;

/** The hidden GLView editor. Native EditBox controls use their own input chain. */
public class TextInputWrapper implements TextWatcher, OnEditorActionListener {
    private final CocosGLSurfaceView mGLSurfaceView;
    private String mText = "";
    private int mBatchDepth;
    private long mConnectionSerial;
    private boolean mActive;

    public TextInputWrapper(final CocosGLSurfaceView view) {
        mGLSurfaceView = view;
    }

    public void setOriginText(final String text) {
        mText = text;
        mBatchDepth = 0;
        ++mConnectionSerial;
        mActive = true;
    }

    void deactivate() {
        mActive = false;
        ++mConnectionSerial;
        mBatchDepth = 0;
    }

    void resetForNativeCaret() {
        final Editable editable = mGLSurfaceView.getEditText().getText();
        BaseInputConnection.removeComposingSpans(editable);
        flushCommittedText();
        // Native navigation/selection changes the real caret. Do not let Android
        // later autocorrect or delete text buffered at the previous caret.
        mGLSurfaceView.getEditText().removeTextChangedListener(this);
        editable.clear();
        setOriginText("");
        mGLSurfaceView.getEditText().addTextChangedListener(this);
    }

    private void beginEdit() {
        ++mBatchDepth;
    }

    private void endEdit() {
        if (mBatchDepth > 0) --mBatchDepth;
        if (mBatchDepth == 0) flushCommittedText();
    }

    private void flushCommittedText() {
        if (!mActive || mBatchDepth != 0 || !mGLSurfaceView.isCurrentHost()) return;
        final Editable editable = mGLSurfaceView.getEditText().getText();
        // setComposingText may replace the same range repeatedly. Never publish its
        // provisional Latin syllables (or delete committed text) until it is final.
        if (BaseInputConnection.getComposingSpanStart(editable) >= 0) return;
        final String text = editable.toString();
        int prefix = 0;
        while (prefix < mText.length() && prefix < text.length()) {
            final int oldPoint = mText.codePointAt(prefix);
            if (oldPoint != text.codePointAt(prefix)) break;
            prefix += Character.charCount(oldPoint);
        }
        final int deleted = mText.codePointCount(prefix, mText.length());
        if (deleted > 0) mGLSurfaceView.deleteBackward(deleted);
        if (prefix < text.length()) mGLSurfaceView.insertText(text.substring(prefix));
        mText = text;
    }

    InputConnection wrap(final InputConnection target) {
        final long serial = mConnectionSerial;
        return new InputConnectionWrapper(target, false) {
            private boolean isCurrent() {
                return mActive && serial == mConnectionSerial && mGLSurfaceView.isCurrentHost();
            }

            @Override
            public boolean beginBatchEdit() {
                if (!isCurrent()) return false;
                beginEdit();
                return super.beginBatchEdit();
            }

            @Override
            public boolean endBatchEdit() {
                if (!isCurrent()) return false;
                try { return super.endBatchEdit(); }
                finally { endEdit(); }
            }

            @Override
            public boolean setComposingText(CharSequence text, int cursor) {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.setComposingText(text, cursor); }
                finally { endEdit(); }
            }

            @Override
            public boolean commitText(CharSequence text, int cursor) {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.commitText(text, cursor); }
                finally { endEdit(); }
            }

            @Override
            public boolean finishComposingText() {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.finishComposingText(); }
                finally { endEdit(); }
            }

            @Override
            public boolean deleteSurroundingText(int before, int after) {
                if (!isCurrent()) return false;
                if (deleteBeforeEmptyEditor(before, after)) return true;
                beginEdit();
                try { return super.deleteSurroundingText(before, after); }
                finally { endEdit(); }
            }

            @Override
            public boolean deleteSurroundingTextInCodePoints(int before, int after) {
                if (!isCurrent()) return false;
                if (deleteBeforeEmptyEditor(before, after)) return true;
                beginEdit();
                try { return super.deleteSurroundingTextInCodePoints(before, after); }
                finally { endEdit(); }
            }
        };
    }

    private boolean deleteBeforeEmptyEditor(int before, int after) {
        if (mActive && mGLSurfaceView.isCurrentHost() && before > 0 && after == 0
                && mGLSurfaceView.getEditText().length() == 0) {
            // ImGui owns the real cursor/text; this editor only buffers new IME text.
            mGLSurfaceView.deleteBackward(before);
            return true;
        }
        return false;
    }

    @Override
    public void afterTextChanged(final Editable text) {
        // A TextWatcher can run before the IME installs its composing span.
        // InputConnection operations flush at their end; plain hardware edits flush
        // on the next UI task after all spans have been updated.
        mGLSurfaceView.post(this::flushCommittedText);
    }

    @Override
    public void beforeTextChanged(CharSequence text, int start, int count, int after) {}

    @Override
    public void onTextChanged(CharSequence text, int start, int before, int count) {}

    @Override
    public boolean onEditorAction(TextView view, int action, KeyEvent event) {
        if (view != mGLSurfaceView.getEditText() || !mActive) return false;
        if (event != null && event.getAction() != KeyEvent.ACTION_DOWN) return true;
        if (action == EditorInfo.IME_ACTION_DONE || action == EditorInfo.IME_ACTION_GO
                || action == EditorInfo.IME_ACTION_SEND || action == EditorInfo.IME_ACTION_SEARCH
                || action == EditorInfo.IME_NULL) {
            BaseInputConnection.removeComposingSpans(mGLSurfaceView.getEditText().getText());
            flushCommittedText();
            mGLSurfaceView.insertText("\n");
            // The native delegate consumes Enter before closing the keyboard.
            // Closing here could drop the queued final commit before a frame.
            return true;
        }
        return false;
    }
}
