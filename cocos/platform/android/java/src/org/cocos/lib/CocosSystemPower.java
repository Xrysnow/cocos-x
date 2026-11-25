package org.cocos.lib;

import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.BatteryManager;
import android.os.PowerManager;

final class CocosSystemPower {
    private CocosSystemPower() {}

    private static String chargingState(int status) {
        switch (status) {
            case BatteryManager.BATTERY_STATUS_CHARGING:
                return "charging";
            case BatteryManager.BATTERY_STATUS_DISCHARGING:
                return "discharging";
            case BatteryManager.BATTERY_STATUS_FULL:
                return "full";
            case BatteryManager.BATTERY_STATUS_NOT_CHARGING:
                return "notCharging";
            default:
                return null;
        }
    }

    static String[] battery() {
        Context context = CocosSystemInfo.applicationContext();
        if (context == null) {
            return new String[] { "", "pending" };
        }
        // A null receiver reads the sticky system snapshot without registering
        // any long-lived receiver or changing battery monitoring policy.
        Intent state = context.registerReceiver(null, new IntentFilter(Intent.ACTION_BATTERY_CHANGED));
        if (state == null) {
            return new String[] { "", "pending" };
        }
        boolean presentKnown = state.hasExtra(BatteryManager.EXTRA_PRESENT);
        boolean present = state.getBooleanExtra(BatteryManager.EXTRA_PRESENT, false);
        boolean absent = presentKnown && !present;
        int level = state.getIntExtra(BatteryManager.EXTRA_LEVEL, -1);
        int scale = state.getIntExtra(BatteryManager.EXTRA_SCALE, -1);
        int plugged = state.getIntExtra(BatteryManager.EXTRA_PLUGGED, -1);
        int status = state.getIntExtra(BatteryManager.EXTRA_STATUS, -1);
        String source = plugged > 0 ? "external" : plugged == 0 && present ? "battery" : null;
        boolean validCharge = !absent && level >= 0 && scale > 0 && level <= scale;
        return new String[] {
            "present", presentKnown ? Boolean.toString(present) : null,
            "level", validCharge ? Integer.toString(level) : null,
            "scale", validCharge ? Integer.toString(scale) : null,
            "chargeFraction:", absent ? "notApplicable" : null,
            "chargingState", absent ? null : chargingState(status),
            "chargingState:", absent ? "notApplicable" : null,
            "powerSource", source
        };
    }

    static String[] profile() {
        Context context = CocosSystemInfo.applicationContext();
        if (context == null) {
            return new String[] { "profile:", "pending", "lowPowerMode:", "pending" };
        }
        PowerManager manager = context.getSystemService(PowerManager.class);
        if (manager == null) {
            return new String[] { "profile:", "unsupported", "lowPowerMode:", "unsupported" };
        }
        boolean powerSave = manager.isPowerSaveMode();
        return new String[] {
            "profile", powerSave ? "powerSaver" : null,
            "lowPowerMode", Boolean.toString(powerSave),
            "powerPlan:", "unsupported"
        };
    }
}
