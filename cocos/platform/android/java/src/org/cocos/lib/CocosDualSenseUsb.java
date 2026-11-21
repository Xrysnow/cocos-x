package org.cocos.lib;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbConstants;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbEndpoint;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;
import android.hardware.usb.UsbRequest;
import android.os.Build;
import android.os.Handler;
import android.os.SystemClock;
import android.util.Log;

import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.TimeoutException;

/** USB Host transport for the standard DualSense. Report semantics live in DualSenseReports. */
final class CocosDualSenseUsb {
    private static final String TAG = "CocosDualSenseUsb";
    private static final int INPUT_BYTES = 64, OUTPUT_BYTES = 63, CALIBRATION_BYTES = 41;
    private final Context context;
    private final Handler handler;
    private final long host;
    private final UsbManager manager;
    private final String permissionAction;
    private final Map<String, Session> sessions = new HashMap<>();
    private final Set<String> requested = new HashSet<>(), failed = new HashSet<>();
    private final Runnable poll = this::scan;
    private final BroadcastReceiver permission = new BroadcastReceiver() {
        @Override public void onReceive(Context context, Intent intent) {
            UsbDevice device = intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);
            if (device != null && device.getDeviceName().equals(permissionPath)) permissionPath = null;
            rescan();
        }
    };
    private boolean resumed;
    private String permissionPath;

    static boolean isDualSense(int vendor, int product) { return vendor == 0x054c && product == 0x0ce6; }

    CocosDualSenseUsb(Context context, Handler handler, long host) {
        this.context = context;
        this.handler = handler;
        this.host = host;
        manager = context.getSystemService(UsbManager.class);
        permissionAction = context.getPackageName() + ".COCOS_DUALSENSE_USB_PERMISSION";
        if (manager != null) {
            IntentFilter filter = new IntentFilter(permissionAction);
            if (Build.VERSION.SDK_INT >= 33) context.registerReceiver(permission, filter, Context.RECEIVER_NOT_EXPORTED);
            else context.registerReceiver(permission, filter);
        }
    }

    void setResumed(boolean value) {
        if (resumed == value) return;
        resumed = value;
        if (resumed) {
            failed.clear();
            rescan();
        } else {
            handler.removeCallbacks(poll);
            for (Session session : sessions.values()) session.stop();
        }
    }

    void close() {
        setResumed(false);
        if (manager != null) context.unregisterReceiver(permission);
    }

    private void rescan() {
        handler.removeCallbacks(poll);
        if (resumed && manager != null) handler.post(poll);
    }

    private void scan() {
        Map<String, UsbDevice> connected = manager.getDeviceList();
        if (permissionPath != null && !connected.containsKey(permissionPath)) permissionPath = null;
        requested.retainAll(connected.keySet());
        failed.retainAll(connected.keySet());
        for (Map.Entry<String, Session> entry : sessions.entrySet())
            if (!connected.containsKey(entry.getKey())) entry.getValue().stop();
        for (UsbDevice device : connected.values()) {
            String path = device.getDeviceName();
            if (!isDualSense(device.getVendorId(), device.getProductId())
                || sessions.containsKey(path) || failed.contains(path)) continue;
            if (!manager.hasPermission(device)) {
                if (permissionPath == null && requested.add(path)) {
                    Intent intent = new Intent(permissionAction).setPackage(context.getPackageName());
                    int flags = PendingIntent.FLAG_ONE_SHOT;
                    if (Build.VERSION.SDK_INT >= 31) flags |= PendingIntent.FLAG_MUTABLE;
                    try {
                        manager.requestPermission(device, PendingIntent.getBroadcast(
                            context, device.getDeviceId(), intent, flags));
                        permissionPath = path;
                    } catch (RuntimeException failure) {
                        Log.w(TAG, "Could not request DualSense USB permission", failure);
                    }
                    // Present at most one permission dialog at a time.
                    break;
                }
                continue;
            }
            Session session = new Session(device);
            sessions.put(path, session);
            new Thread(session::run, "DualSense USB").start();
        }
        handler.postDelayed(poll, 750);
    }

    private final class Session {
        final UsbDevice device;
        final int id;
        final long endpoint = CocosGamepads.nextEndpoint();
        volatile boolean stopping;
        UsbRequest inputRequest, outputRequest;

        Session(UsbDevice device) {
            this.device = device;
            id = -1 - device.getDeviceId();
        }

        synchronized void stop() {
            stopping = true;
            if (inputRequest != null) inputRequest.cancel();
            if (outputRequest != null) outputRequest.cancel();
        }

        private synchronized boolean queue(UsbRequest request, ByteBuffer buffer) {
            if (stopping) return false;
            return Build.VERSION.SDK_INT >= 26 ? request.queue(buffer) : request.queue(buffer, buffer.remaining());
        }

        void run() {
            try {
                for (int i = 0; !stopping && i < device.getInterfaceCount(); ++i) {
                    UsbInterface intf = device.getInterface(i);
                    if (intf.getInterfaceClass() != UsbConstants.USB_CLASS_HID) continue;
                    UsbEndpoint in = null, out = null;
                    for (int j = 0; j < intf.getEndpointCount(); ++j) {
                        UsbEndpoint candidate = intf.getEndpoint(j);
                        if (candidate.getType() != UsbConstants.USB_ENDPOINT_XFER_INT) continue;
                        if (candidate.getDirection() == UsbConstants.USB_DIR_IN
                            && candidate.getMaxPacketSize() >= INPUT_BYTES) in = candidate;
                        if (candidate.getDirection() == UsbConstants.USB_DIR_OUT
                            && candidate.getMaxPacketSize() >= OUTPUT_BYTES) out = candidate;
                    }
                    if (in != null && out != null) {
                        open(intf, in, out);
                        break;
                    }
                }
            } catch (RuntimeException failure) {
                if (!stopping) Log.w(TAG, "DualSense USB transport closed", failure);
            } finally {
                nativeClose(host, id, endpoint);
                handler.post(() -> {
                    String path = device.getDeviceName();
                    sessions.remove(path, this);
                    if (!stopping) failed.add(path);
                    rescan();
                });
            }
        }

        private void open(UsbInterface intf, UsbEndpoint in, UsbEndpoint out) {
            UsbDeviceConnection link = manager.openDevice(device);
            if (link == null) return;
            boolean claimed = false;
            boolean stopped = false;
            try {
                // The kernel input driver is detached when the HID interface is taken over.
                // A denied grant or failed claim leaves Android's normal InputDevice path available.
                claimed = !stopping && link.claimInterface(intf, true);
                if (!claimed || stopping) return;
                byte[] calibration = new byte[CALIBRATION_BYTES];
                int length = link.controlTransfer(0xa1, 0x01, 0x0305, intf.getId(),
                    calibration, calibration.length, 500);
                if (stopping || !nativeOpen(host, id, endpoint, length == calibration.length ? calibration : null)) return;
                stopped = stream(link, in, out);
            } finally {
                nativeClose(host, id, endpoint);
                try {
                    if (claimed) {
                        try {
                            if (!stopped) {
                                byte[] packet = new byte[OUTPUT_BYTES];
                                nativeNeutral(packet);
                                link.controlTransfer(0x21, 0x09, 0x0202, intf.getId(), packet, packet.length, 150);
                            }
                        } finally { link.releaseInterface(intf); }
                    }
                }
                finally { link.close(); }
            }
        }

        private boolean stream(UsbDeviceConnection link, UsbEndpoint in, UsbEndpoint out) {
            UsbRequest read = new UsbRequest(), write = new UsbRequest();
            boolean reading = false, writing = false;
            try {
                if (!read.initialize(link, in) || !write.initialize(link, out)) return false;
                synchronized (this) {
                    if (stopping) return false;
                    inputRequest = read;
                    outputRequest = write;
                }
                ByteBuffer input = ByteBuffer.allocateDirect(INPUT_BYTES);
                ByteBuffer output = ByteBuffer.allocateDirect(OUTPUT_BYTES);
                byte[] incoming = new byte[INPUT_BYTES], outgoing = new byte[OUTPUT_BYTES];
                long firstReportDeadline = SystemClock.uptimeMillis() + 1000;
                long writeDeadline = 0;
                boolean valid = false;
                while (!stopping) {
                    if (!reading) {
                        ((Buffer) input).clear();
                        if (!queue(read, input)) break;
                        reading = true;
                    }
                    if (!writing && nativeNextOutput(host, id, endpoint, outgoing)) {
                        ((Buffer) output).clear();
                        output.put(outgoing);
                        ((Buffer) output).flip();
                        writing = queue(write, output);
                        if (writing) writeDeadline = SystemClock.uptimeMillis() + 500;
                        else nativeOutputDone(host, id, endpoint, false);
                    }
                    UsbRequest completed;
                    try {
                        completed = Build.VERSION.SDK_INT >= 26 ? link.requestWait(40) : link.requestWait();
                        if (completed == null) break;
                    } catch (TimeoutException timeout) {
                        completed = null;
                    }
                    if (completed == read) {
                        reading = false;
                        int count = input.position();
                        ((Buffer) input).flip();
                        input.get(incoming, 0, count);
                        valid |= nativeRead(host, id, endpoint, incoming, count);
                    } else if (completed == write) {
                        nativeOutputDone(host, id, endpoint, output.position() == OUTPUT_BYTES);
                        writing = false;
                    }
                    long now = SystemClock.uptimeMillis();
                    if (!valid && now >= firstReportDeadline || writing && now >= writeDeadline) break;
                }
                if (writing) nativeOutputDone(host, id, endpoint, false);
                return writeNeutral(link, read, write, reading, writing, outgoing);
            } finally {
                synchronized (this) {
                    inputRequest = null;
                    outputRequest = null;
                    read.close();
                    write.close();
                }
            }
        }

        private boolean writeNeutral(UsbDeviceConnection link, UsbRequest read, UsbRequest write,
                                     boolean reading, boolean writing, byte[] packet) {
            if (reading) read.cancel();
            if (writing) write.cancel();
            if (Build.VERSION.SDK_INT < 26) return false;
            nativeNeutral(packet);
            try {
                long deadline = SystemClock.uptimeMillis() + 150;
                while (reading || writing) {
                    UsbRequest completed = link.requestWait(Math.max(1, deadline - SystemClock.uptimeMillis()));
                    if (completed == null || SystemClock.uptimeMillis() >= deadline) return false;
                    if (completed == read) reading = false;
                    if (completed == write) writing = false;
                }
                ByteBuffer bytes = ByteBuffer.wrap(packet);
                if (!write.queue(bytes)) return false;
                if (link.requestWait(Math.max(1, deadline - SystemClock.uptimeMillis())) == write)
                    return bytes.position() == OUTPUT_BYTES;
                write.cancel();
            } catch (TimeoutException | RuntimeException ignored) {
                write.cancel();
            }
            return false;
        }
    }

    private static native boolean nativeOpen(long host, int id, long endpoint, byte[] calibration);
    private static native boolean nativeRead(long host, int id, long endpoint, byte[] packet, int length);
    private static native boolean nativeNextOutput(long host, int id, long endpoint, byte[] packet);
    private static native void nativeOutputDone(long host, int id, long endpoint, boolean success);
    private static native void nativeClose(long host, int id, long endpoint);
    private static native void nativeNeutral(byte[] packet);
}
