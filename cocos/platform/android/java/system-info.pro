# Calls into this bridge use JNI class names and signatures.
-keep class org.cocos.lib.CocosSystemInfo {
    static java.lang.String[] computer(boolean);
    static java.lang.String[] os();
    static java.lang.String[] memory();
    static java.lang.String[] uptime();
}

-keep class org.cocos.lib.CocosSystemNetwork {
    static java.lang.String[] read();
    static void startEvents();
    static void stopEvents();
    static native void networkChanged();
}

-keep class org.cocos.lib.CocosSystemPower {
    static java.lang.String[] battery();
    static java.lang.String[] profile();
}
