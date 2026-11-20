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
import android.text.Selection;
import android.text.TextWatcher;
import android.view.KeyEvent;
import android.view.inputmethod.BaseInputConnection;
import android.view.inputmethod.CompletionInfo;
import android.view.inputmethod.CorrectionInfo;
import android.view.inputmethod.ExtractedText;
import android.view.inputmethod.ExtractedTextRequest;
import android.view.inputmethod.InputConnection;
import android.view.inputmethod.InputConnectionWrapper;
import android.view.inputmethod.SurroundingText;
import android.view.inputmethod.TextAttribute;
import android.view.inputmethod.TextSnapshot;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;

/** The hidden GLView editor. Native EditBox controls use their own input chain. */
public class TextInputWrapper implements TextWatcher, OnEditorActionListener {
    enum SnapshotResult { UNCHANGED, APPLIED, INVALID }
    // Matches TextInputPreeditPhase on the native side.
    private static final int PREEDIT_BEGAN = 0;
    private static final int PREEDIT_UPDATED = 1;
    private static final int PREEDIT_ENDED = 2;
    private final CocosGLSurfaceView mGLSurfaceView;
    private String mText = "";
    private int mBatchDepth;
    private long mConnectionSerial;
    private boolean mActive;
    private Integer mPendingEditorAction;
    private boolean mRangeReady;
    private boolean mObservePreedit;
    private String mPreedit;
    private int mPreeditAnchor;
    private int mPreeditFocus;
    private long mSnapshotEpoch;
    private long mRevision;
    private long mTransaction;
    private long mOrigin;
    private int mAnchor;
    private int mFocus;

    public TextInputWrapper(final CocosGLSurfaceView view) {
        mGLSurfaceView = view;
    }

    void activate(boolean observePreedit) {
        mText = "";
        mBatchDepth = 0;
        mPendingEditorAction = null;
        ++mConnectionSerial;
        mActive = true;
        mRangeReady = false;
        mObservePreedit = observePreedit;
        mPreedit = null;
        mTransaction = 0;
    }

    void deactivate() {
        mActive = false;
        mRangeReady = false;
        mObservePreedit = false;
        mPreedit = null;
        mText = "";
        ++mConnectionSerial;
        mBatchDepth = 0;
        mPendingEditorAction = null;
    }

    boolean isRangeReady() {
        return mRangeReady;
    }

    SnapshotResult setSnapshot(long epoch, long revision, long acknowledged, long origin,
            String text, int anchor, int focus) {
        if (mRangeReady && Long.compareUnsigned(epoch, mSnapshotEpoch) <= 0) {
            // The engine acknowledged an edit in the same epoch. A later edit may
            // already be reflected in this Editable; preserve its text and selection.
            if (epoch != mSnapshotEpoch || (acknowledged != 0 && Long.compareUnsigned(revision, mRevision) <= 0))
                return SnapshotResult.UNCHANGED;
        }

        finishObservation();
        final CocosEditBox editor = mGLSurfaceView.getEditText();
        editor.removeTextChangedListener(this);
        ++mConnectionSerial;
        editor.setText(text);
        final Editable editable = editor.getText();
        if (!text.contentEquals(editable) || anchor < 0 || focus < 0 ||
                anchor > editable.length() || focus > editable.length()) return SnapshotResult.INVALID;
        Selection.setSelection(editable, anchor, focus);
        mRangeReady = true;
        mSnapshotEpoch = epoch;
        mRevision = revision;
        mOrigin = origin;
        mText = text;
        mAnchor = anchor;
        mFocus = focus;
        mBatchDepth = 0;
        mPendingEditorAction = null;
        editor.addTextChangedListener(this);
        return SnapshotResult.APPLIED;
    }

    boolean cancelComposition() {
        if (mRangeReady)
            return setSnapshot(mSnapshotEpoch, mRevision, 0, mOrigin, mText, mAnchor, mFocus) != SnapshotResult.INVALID;
        finishObservation();
        final CocosEditBox editor = mGLSurfaceView.getEditText();
        editor.removeTextChangedListener(this);
        editor.setText("");
        activate(mObservePreedit);
        editor.addTextChangedListener(this);
        return true;
    }

    void afterSelectionChanged() {
        if (mActive && (mRangeReady || mObservePreedit)) scheduleFlush();
    }

    int compositionKnowledge() {
        // TextInputKnowledge: unknown, no, yes.
        return !mObservePreedit ? 0 : mPreedit != null ? 2 : 1;
    }

    void finishObservation() {
        if (mPreedit == null) return;
        mPreedit = null;
        mGLSurfaceView.observeTextInputPreedit("", PREEDIT_ENDED, -1, -1);
    }

    private void observeComposition(Editable editable, int start, int end) {
        if (!mObservePreedit) return;
        final String text = editable.subSequence(start, end).toString();
        final int selectionStart = Selection.getSelectionStart(editable);
        final int selectionEnd = Selection.getSelectionEnd(editable);
        final boolean selectionKnown = selectionStart >= start && selectionStart <= end &&
                selectionEnd >= start && selectionEnd <= end;
        final int anchor = selectionKnown ? selectionStart - start : -1;
        final int focus = selectionKnown ? selectionEnd - start : -1;
        if (text.equals(mPreedit) && anchor == mPreeditAnchor && focus == mPreeditFocus) return;
        final int phase = mPreedit == null ? PREEDIT_BEGAN : PREEDIT_UPDATED;
        mPreedit = text;
        mPreeditAnchor = anchor;
        mPreeditFocus = focus;
        mGLSurfaceView.observeTextInputPreedit(text, phase, anchor, focus);
    }

    private void beginEdit() {
        ++mBatchDepth;
    }

    private void endEdit() {
        if (mBatchDepth > 0) --mBatchDepth;
        if (mBatchDepth != 0) return;
        if (mPendingEditorAction == null) {
            flushCommittedText();
        } else {
            final int action = mPendingEditorAction;
            mPendingEditorAction = null;
            finishEditorAction(action);
        }
    }

    void flushCommittedText() {
        if (!mActive || mBatchDepth != 0 || !mGLSurfaceView.isCurrentHost()) return;
        final Editable editable = mGLSurfaceView.getEditText().getText();
        // setComposingText may replace the same range repeatedly. Never publish its
        // provisional Latin syllables (or delete committed text) until it is final.
        final int composingStart = BaseInputConnection.getComposingSpanStart(editable);
        final int composingEnd = BaseInputConnection.getComposingSpanEnd(editable);
        if (composingStart >= 0 && composingEnd >= 0) {
            observeComposition(editable, Math.min(composingStart, composingEnd), Math.max(composingStart, composingEnd));
            return;
        }
        finishObservation();
        final String text = editable.toString();
        if (mRangeReady) {
            final int anchor = Selection.getSelectionStart(editable);
            final int focus = Selection.getSelectionEnd(editable);
            if (anchor >= 0 && focus >= 0 && (!mText.equals(text) || anchor != mAnchor || focus != mFocus)) {
                if (mGLSurfaceView.editTextInput(mSnapshotEpoch, mRevision, ++mTransaction, mOrigin,
                        mText, text, anchor, focus)) {
                    ++mRevision;
                    mText = text;
                    mAnchor = anchor;
                    mFocus = focus;
                }
            }
            return;
        }
        mGLSurfaceView.commitTextInput(text);
        // The field owns committed text. Keep only unconfirmed text in this editor.
        if (!text.isEmpty()) editable.clear();
    }

    InputConnection wrap(final InputConnection target) {
        final long serial = ++mConnectionSerial;
        mBatchDepth = 0;
        mPendingEditorAction = null;
        scheduleFlush();
        return new InputConnectionWrapper(target, false) {
            private boolean isCurrent() {
                return mActive && serial == mConnectionSerial && mGLSurfaceView.isCurrentHost();
            }

            @Override
            public boolean beginBatchEdit() {
                if (!isCurrent() || !super.beginBatchEdit()) return false;
                beginEdit();
                return true;
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
            public boolean setComposingText(CharSequence text, int cursor, TextAttribute attribute) {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.setComposingText(text, cursor, attribute); }
                finally { endEdit(); }
            }

            @Override
            public boolean setComposingRegion(int start, int end) {
                return isCurrent() && super.setComposingRegion(start, end);
            }

            @Override
            public boolean setComposingRegion(int start, int end, TextAttribute attribute) {
                return isCurrent() && super.setComposingRegion(start, end, attribute);
            }

            @Override
            public boolean commitText(CharSequence text, int cursor) {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.commitText(text, cursor); }
                finally { endEdit(); }
            }

            @Override
            public boolean commitText(CharSequence text, int cursor, TextAttribute attribute) {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.commitText(text, cursor, attribute); }
                finally { endEdit(); }
            }

            @Override
            public boolean commitCompletion(CompletionInfo completion) {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.commitCompletion(completion); }
                finally { endEdit(); }
            }

            @Override
            public boolean commitCorrection(CorrectionInfo correction) {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.commitCorrection(correction); }
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
                if (hasEmptySessionEditor()) return mGLSurfaceView.deleteTextInput(before, after);
                beginEdit();
                try { return super.deleteSurroundingText(before, after); }
                finally { endEdit(); }
            }

            @Override
            public boolean deleteSurroundingTextInCodePoints(int before, int after) {
                if (!isCurrent()) return false;
                if (hasEmptySessionEditor()) return mGLSurfaceView.deleteTextInput(before, after);
                beginEdit();
                try { return super.deleteSurroundingTextInCodePoints(before, after); }
                finally { endEdit(); }
            }

            @Override
            public boolean requestCursorUpdates(int mode) {
                return isCurrent() && mGLSurfaceView.requestTextInputCursorUpdates(mode);
            }

            @Override
            public boolean requestCursorUpdates(int mode, int filter) {
                return isCurrent() && mGLSurfaceView.requestTextInputCursorUpdates(mode);
            }

            @Override
            public boolean setSelection(int start, int end) {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.setSelection(start, end); }
                finally { endEdit(); }
            }

            @Override
            public boolean performEditorAction(int action) {
                return isCurrent() && super.performEditorAction(action);
            }

            @Override
            public boolean performContextMenuAction(int action) {
                return isCurrent() && super.performContextMenuAction(action);
            }

            @Override
            public boolean sendKeyEvent(KeyEvent event) {
                return isCurrent() && mGLSurfaceView.getEditText().dispatchKeyEvent(event);
            }

            @Override
            public boolean replaceText(int start, int end, CharSequence text, int cursor, TextAttribute attribute) {
                if (!isCurrent()) return false;
                beginEdit();
                try { return super.replaceText(start, end, text, cursor, attribute); }
                finally { endEdit(); }
            }

            @Override
            public CharSequence getTextBeforeCursor(int length, int flags) {
                return isCurrent() ? super.getTextBeforeCursor(length, flags) : null;
            }

            @Override
            public CharSequence getTextAfterCursor(int length, int flags) {
                return isCurrent() ? super.getTextAfterCursor(length, flags) : null;
            }

            @Override
            public CharSequence getSelectedText(int flags) {
                return isCurrent() ? super.getSelectedText(flags) : null;
            }

            @Override
            public ExtractedText getExtractedText(ExtractedTextRequest request, int flags) {
                return isCurrent() ? super.getExtractedText(request, flags) : null;
            }

            @Override
            public SurroundingText getSurroundingText(int before, int after, int flags) {
                return isCurrent() ? super.getSurroundingText(before, after, flags) : null;
            }

            @Override
            public TextSnapshot takeSnapshot() {
                return isCurrent() ? super.takeSnapshot() : null;
            }

            @Override
            public void closeConnection() {
                super.closeConnection();
                if (!isCurrent()) return;
                ++mConnectionSerial;
                mBatchDepth = 0;
                mPendingEditorAction = null;
                scheduleFlush();
            }
        };
    }

    private boolean hasEmptySessionEditor() {
        return !mRangeReady && mGLSurfaceView.getEditText().length() == 0;
    }

    @Override
    public void afterTextChanged(final Editable text) {
        // A TextWatcher can run before the IME installs its composing span.
        // InputConnection operations flush at their end; plain hardware edits flush
        // on the next UI task after all spans have been updated.
        scheduleFlush();
    }

    private void scheduleFlush() {
        final long serial = mConnectionSerial;
        mGLSurfaceView.post(() -> {
            if (serial == mConnectionSerial) flushCommittedText();
        });
    }

    @Override
    public void beforeTextChanged(CharSequence text, int start, int count, int after) {}

    @Override
    public void onTextChanged(CharSequence text, int start, int before, int count) {}

    @Override
    public boolean onEditorAction(TextView view, int action, KeyEvent event) {
        if (view != mGLSurfaceView.getEditText() || !mActive) return false;
        if (event != null && event.getAction() != KeyEvent.ACTION_DOWN) return true;
        if (mBatchDepth != 0) {
            mPendingEditorAction = action;
            return true;
        }
        return finishEditorAction(action);
    }

    private boolean finishEditorAction(int action) {
        BaseInputConnection.removeComposingSpans(mGLSurfaceView.getEditText().getText());
        flushCommittedText();
        return mGLSurfaceView.handleTextInputEditorAction(action);
    }
}
