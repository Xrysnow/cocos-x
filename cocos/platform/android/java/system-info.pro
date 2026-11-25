# Calls into this bridge use JNI class names and signatures.
-keep class org.cocos.lib.CocosSystemInfo {
    static java.lang.String[] computer(boolean);
    static java.lang.String[] os();
    static java.lang.String[] memory();
    static java.lang.String[] uptime();
}
