package org.cocos.demo;

import android.os.Bundle;
import org.cocos.lib.CocosActivity;

public class AppActivity extends CocosActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);
    }
}
