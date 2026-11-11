package org.cocos.demo;

import android.os.Bundle;
import org.cocos.lib.GameControllerActivity;

public class AppActivity extends GameControllerActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);
    }
}
