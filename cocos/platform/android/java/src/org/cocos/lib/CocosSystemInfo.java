package org.cocos.lib;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.SystemClock;

final class CocosSystemInfo {
    private CocosSystemInfo() {}

    static Context applicationContext() {
        Context activity = CocosActivity.getContext();
        return activity == null ? null : activity.getApplicationContext();
    }

    private static String known(String value) {
        return value == null || value.trim().isEmpty() || Build.UNKNOWN.equalsIgnoreCase(value)
                ? null : value;
    }

    private static String chassis() {
        Context context = applicationContext();
        if (context == null) {
            return null;
        }
        PackageManager pm = context.getPackageManager();
        if (pm.hasSystemFeature(PackageManager.FEATURE_AUTOMOTIVE)
                || pm.hasSystemFeature(PackageManager.FEATURE_LEANBACK)
                || pm.hasSystemFeature(PackageManager.FEATURE_WATCH)
                || pm.hasSystemFeature(PackageManager.FEATURE_EMBEDDED)) {
            return "other";
        }
        // Android's public feature flags do not distinguish a phone from a
        // tablet with the same telephony capabilities.
        return null;
    }

    @SuppressWarnings("deprecation")
    static String[] computer(boolean identifiers) {
        String serial = null;
        String serialStatus = "withheld";
        if (identifiers) {
            serialStatus = null;
            try {
                serial = known(Build.VERSION.SDK_INT >= 26 ? Build.getSerial() : Build.SERIAL);
            } catch (SecurityException ignored) {
                serialStatus = "permissionDenied";
            }
        }
        return new String[] {
            "vendor", known(Build.MANUFACTURER),
            "model", known(CocosEngine.getDeviceModel()),
            "chassis", chassis(),
            "sku", Build.VERSION.SDK_INT >= 31 ? known(Build.SKU) : null,
            "sku:", Build.VERSION.SDK_INT < 31 ? "unsupported" : null,
            "serialNumber", serial,
            "serialNumber:", serialStatus,
            "uuid:", identifiers ? "unsupported" : "withheld",
            "socModel", Build.VERSION.SDK_INT >= 31 ? known(Build.SOC_MODEL) : null,
            "socModel:", Build.VERSION.SDK_INT < 31 ? "unsupported" : null
        };
    }

    static String[] os() {
        final String abi = Build.SUPPORTED_ABIS.length == 0 ? null : Build.SUPPORTED_ABIS[0];
        return new String[] {
            "family", "Android",
            "name", "Android",
            "marketingName", "Android",
            "version", known(Build.VERSION.RELEASE),
            "build", known(Build.ID),
            "abi", abi
        };
    }

    static String[] memory() {
        Context context = applicationContext();
        if (context == null) {
            return new String[] { "", "pending" };
        }
        ActivityManager am = context.getSystemService(ActivityManager.class);
        if (am == null) {
            return new String[] { "", "unsupported" };
        }
        ActivityManager.MemoryInfo info = new ActivityManager.MemoryInfo();
        am.getMemoryInfo(info);
        return new String[] {
            "total", info.totalMem > 0 ? Long.toString(info.totalMem) : null,
            "available", info.availMem >= 0 ? Long.toString(info.availMem) : null
        };
    }

    static String[] uptime() {
        long before = SystemClock.elapsedRealtime();
        long wall = System.currentTimeMillis();
        long after = SystemClock.elapsedRealtime();
        long boot = wall - (before + (after - before) / 2);
        return new String[] {
            "elapsedMillis", Long.toString(after),
            "bootMillis", boot > 0 ? Long.toString(boot) : null
        };
    }
}
