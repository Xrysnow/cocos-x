# The Android TextInput backend looks up this bridge by name.
-keep class org.cocos.lib.CocosGLSurfaceView {
    public static boolean activateTextInput(long,int,int,int,boolean,int,boolean,boolean);
    public static boolean requestTextInputKeyboard(long,boolean);
    public static boolean cancelTextInputComposition(long);
    public static boolean hasTextInputKeyboardVisibility();
    public static boolean closeTextInput(long);
    public static void setTextInputArea(long,boolean,float,float,float);
    public static void setTextInputSnapshot(long,long,long,long,long,java.lang.String,int,int);
    private static native <methods>;
}
