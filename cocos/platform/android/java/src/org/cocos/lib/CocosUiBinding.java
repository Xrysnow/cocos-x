package org.cocos.lib;

import android.app.Activity;
import android.os.Handler;
import android.os.Looper;

import java.util.ArrayDeque;

/** Asynchronous UI commands with an explicit Activity handoff boundary. */
final class CocosUiBinding {
    private final Handler ui = new Handler(Looper.getMainLooper());
    private final ArrayDeque<Runnable> pending = new ArrayDeque<>();
    private Activity activity;
    private boolean accepting;

    void bind(Activity owner) {
        synchronized (pending) {
            activity = owner;
            accepting = true;
        }
    }

    boolean post(Runnable task) {
        final Activity owner;
        synchronized (pending) {
            if (!accepting) return false;
            owner = activity;
            pending.addLast(task);
        }
        ui.post(() -> drain(owner));
        return true;
    }

    // Called on UI before releasing/reparenting helper views. Finish accepted
    // native mutations (including pending creates/removes) so their tags and
    // state survive recreation; reject subsequent commands from the old host.
    void unbind(Activity owner) {
        synchronized (pending) {
            if (activity != owner) return;
            accepting = false;
        }
        drain(owner);
        synchronized (pending) {
            activity = null;
        }
    }

    private void drain(Activity owner) {
        for (;;) {
            final Runnable task;
            synchronized (pending) {
                if (activity != owner) return;
                task = pending.pollFirst();
            }
            if (task == null) return;
            task.run();
        }
    }
}
