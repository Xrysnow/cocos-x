package org.cocos.lib;

import android.annotation.SuppressLint;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkSpecifier;
import android.net.TelephonyNetworkSpecifier;
import android.os.Build;
import android.telephony.SubscriptionManager;
import android.telephony.TelephonyManager;

import java.util.Objects;

final class CocosSystemNetwork {
    private static final int[] TRANSPORTS = {
        NetworkCapabilities.TRANSPORT_WIFI, NetworkCapabilities.TRANSPORT_CELLULAR,
        NetworkCapabilities.TRANSPORT_ETHERNET, NetworkCapabilities.TRANSPORT_BLUETOOTH,
        NetworkCapabilities.TRANSPORT_WIFI_AWARE, NetworkCapabilities.TRANSPORT_LOWPAN,
        NetworkCapabilities.TRANSPORT_USB, NetworkCapabilities.TRANSPORT_THREAD,
        NetworkCapabilities.TRANSPORT_SATELLITE
    };
    private static final String[] TRANSPORT_NAMES = {
        "wifi", "cellular", "ethernet", "bluetooth", "other", "other", "other", "other", "other"
    };
    private static volatile ConnectivityManager.NetworkCallback callback;
    private static ConnectivityManager callbackManager;

    private CocosSystemNetwork() {}

    private static Network defaultNetwork(ConnectivityManager manager) {
        Network bound = manager.getBoundNetworkForProcess();
        return bound != null ? bound : manager.getActiveNetwork();
    }

    private static String primaryType(NetworkCapabilities caps, boolean vpn) {
        String result = null;
        for (int i = 0; i < TRANSPORTS.length; i++) {
            if (caps.hasTransport(TRANSPORTS[i])) {
                if (result != null) {
                    return null;
                }
                result = TRANSPORT_NAMES[i];
            }
        }
        return result == null && !vpn ? "other" : result;
    }

    private static String generation(int type) {
        switch (type) {
            case TelephonyManager.NETWORK_TYPE_GPRS:
            case TelephonyManager.NETWORK_TYPE_EDGE:
            case TelephonyManager.NETWORK_TYPE_CDMA:
            case TelephonyManager.NETWORK_TYPE_1xRTT:
            case TelephonyManager.NETWORK_TYPE_IDEN:
            case TelephonyManager.NETWORK_TYPE_GSM:
                return "2G";
            case TelephonyManager.NETWORK_TYPE_UMTS:
            case TelephonyManager.NETWORK_TYPE_EVDO_0:
            case TelephonyManager.NETWORK_TYPE_EVDO_A:
            case TelephonyManager.NETWORK_TYPE_EVDO_B:
            case TelephonyManager.NETWORK_TYPE_HSDPA:
            case TelephonyManager.NETWORK_TYPE_HSUPA:
            case TelephonyManager.NETWORK_TYPE_HSPA:
            case TelephonyManager.NETWORK_TYPE_EHRPD:
            case TelephonyManager.NETWORK_TYPE_HSPAP:
            case TelephonyManager.NETWORK_TYPE_TD_SCDMA:
                return "3G";
            case TelephonyManager.NETWORK_TYPE_LTE:
            case 19: // LTE carrier aggregation
                return "4G";
            case TelephonyManager.NETWORK_TYPE_NR:
                return "5G";
            default:
                return null;
        }
    }

    private static int dataSubscription() {
        return Build.VERSION.SDK_INT >= 30
                ? SubscriptionManager.getActiveDataSubscriptionId()
                : SubscriptionManager.getDefaultDataSubscriptionId();
    }

    private static final class Cellular {
        final String generation;
        final String status;

        Cellular(String generation, String status) {
            this.generation = generation;
            this.status = status;
        }
    }

    @SuppressLint("MissingPermission")
    @SuppressWarnings("deprecation")
    private static Cellular cellular(Context context, NetworkCapabilities caps, boolean vpnOrBound) {
        TelephonyManager telephony = context.getSystemService(TelephonyManager.class);
        if (telephony == null) {
            return new Cellular(null, "unsupported");
        }
        try {
            int subId = dataSubscription();
            if (subId == SubscriptionManager.INVALID_SUBSCRIPTION_ID) {
                return new Cellular(null, "unknown");
            }

            boolean subscriptionConfirmed = false;
            if (Build.VERSION.SDK_INT >= 30) {
                NetworkSpecifier specifier = caps.getNetworkSpecifier();
                if (specifier instanceof TelephonyNetworkSpecifier) {
                    if (((TelephonyNetworkSpecifier) specifier).getSubscriptionId() != subId) {
                        return new Cellular(null, "unknown");
                    }
                    subscriptionConfirmed = true;
                }
            }
            // Older releases expose only the configured data SIM. For a VPN or
            // a process-bound network, the bearer might also use another SIM.
            if (!subscriptionConfirmed && (Build.VERSION.SDK_INT < 30 || vpnOrBound)) {
                int modems = Build.VERSION.SDK_INT >= 30
                        ? telephony.getActiveModemCount() : telephony.getPhoneCount();
                if (modems != 1) {
                    return new Cellular(null, "unknown");
                }
            }
            int radio = telephony.createForSubscriptionId(subId).getDataNetworkType();
            if (subId != dataSubscription()) {
                return new Cellular(null, "pending");
            }
            return new Cellular(generation(radio), null);
        } catch (SecurityException ignored) {
            return new Cellular(null, "permissionDenied");
        } catch (UnsupportedOperationException ignored) {
            return new Cellular(null, "unsupported");
        }
    }

    @SuppressLint("MissingPermission")
    static String[] read() {
        Context context = CocosSystemInfo.applicationContext();
        if (context == null) {
            return new String[] { "", "pending" };
        }
        ConnectivityManager manager = context.getSystemService(ConnectivityManager.class);
        if (manager == null) {
            return new String[] { "", "unsupported" };
        }
        try {
            Network active = defaultNetwork(manager);
            if (active == null) {
                return new String[] {
                    "primaryType", "none", "cellularGeneration:", "notApplicable",
                    "isVpn:", "notApplicable", "isMetered:", "notApplicable", "costHint:", "notApplicable"
                };
            }
            NetworkCapabilities caps = manager.getNetworkCapabilities(active);
            if (caps == null) {
                return new String[] { "", "pending" };
            }
            boolean vpn = caps.hasTransport(NetworkCapabilities.TRANSPORT_VPN);
            boolean notVpn = caps.hasCapability(NetworkCapabilities.NET_CAPABILITY_NOT_VPN);
            String primary = primaryType(caps, vpn);
            boolean unmetered = caps.hasCapability(NetworkCapabilities.NET_CAPABILITY_NOT_METERED)
                    || (Build.VERSION.SDK_INT >= 30 && caps.hasCapability(
                            NetworkCapabilities.NET_CAPABILITY_TEMPORARILY_NOT_METERED));
            boolean bound = manager.getBoundNetworkForProcess() != null;
            Cellular cellular = "cellular".equals(primary)
                    ? cellular(context, caps, vpn || bound)
                    : new Cellular(null, primary == null ? "unknown" : "notApplicable");
            if (!Objects.equals(active, defaultNetwork(manager))) {
                return new String[] { "", "pending" };
            }
            return new String[] {
                "primaryType", primary, "cellularGeneration", cellular.generation,
                "cellularGeneration:", cellular.status,
                "isVpn", vpn ? "true" : notVpn ? "false" : null,
                "isMetered", Boolean.toString(!unmetered), "costHint:", "unsupported"
            };
        } catch (SecurityException ignored) {
            return new String[] { "", "permissionDenied" };
        }
    }

    @SuppressLint("MissingPermission")
    static synchronized void startEvents() {
        Context context = CocosSystemInfo.applicationContext();
        if (callback != null || context == null) {
            return;
        }
        ConnectivityManager manager = context.getSystemService(ConnectivityManager.class);
        if (manager == null) {
            return;
        }
        ConnectivityManager.NetworkCallback observer = new ConnectivityManager.NetworkCallback() {
            private void notifyNative() {
                if (callback == this) {
                    networkChanged();
                }
            }

            @Override
            public void onAvailable(Network network) {
                notifyNative();
            }

            @Override
            public void onLost(Network network) {
                notifyNative();
            }

            @Override
            public void onCapabilitiesChanged(Network network, NetworkCapabilities capabilities) {
                notifyNative();
            }

            @Override
            public void onBlockedStatusChanged(Network network, boolean blocked) {
                notifyNative();
            }
        };
        callback = observer;
        try {
            manager.registerDefaultNetworkCallback(observer);
            callbackManager = manager;
        } catch (RuntimeException ignored) {
            // Queries and the native sampler remain available without events.
            callback = null;
        }
    }

    static synchronized void stopEvents() {
        ConnectivityManager.NetworkCallback observer = callback;
        ConnectivityManager manager = callbackManager;
        callback = null;
        callbackManager = null;
        if (observer != null && manager != null) {
            try {
                manager.unregisterNetworkCallback(observer);
            } catch (IllegalArgumentException ignored) {
                // The callback was already removed by the system.
            }
        }
    }

    private static native void networkChanged();
}
