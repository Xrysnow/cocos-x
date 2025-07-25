/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos.lib;

import android.content.Context;
import android.graphics.Typeface;

import java.util.HashMap;

public class TypefaceHelper {
    // ===========================================================
    // Constants
    // ===========================================================

    // ===========================================================
    // Fields
    // ===========================================================

    private static final HashMap<String, Typeface> sTypefaceCache = new HashMap<String, Typeface>();

    // ===========================================================
    // Constructors
    // ===========================================================

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    // ===========================================================
    // Methods
    // ===========================================================

    public static synchronized Typeface get(final Context context, final String assetName) {
        if (!TypefaceHelper.sTypefaceCache.containsKey(assetName)) {
            Typeface typeface = null;
            if (assetName.startsWith("/"))
            {
                typeface = Typeface.createFromFile(assetName);
            }
            else
            {
                typeface = Typeface.createFromAsset(context.getAssets(), assetName);
            }
            TypefaceHelper.sTypefaceCache.put(assetName, typeface);
        }

        return TypefaceHelper.sTypefaceCache.get(assetName);
    }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================

}
