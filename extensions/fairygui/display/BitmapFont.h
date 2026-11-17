#ifndef __BITMAPFONT_H__
#define __BITMAPFONT_H__

#include "FairyGUIMacros.h"
#include "cocos2d.h"
#include "PackageItem.h"

NS_FGUI_BEGIN

class BitmapFont : public cc::Font
{
public:
    BitmapFont();
    virtual ~BitmapFont();

    static cc::IntrusivePtr<BitmapFont> create();

    virtual int* getHorizontalKerningForTextUTF32(const std::u32string& text, int &outNumLetters) const override;
#if defined(CC_VERSION)
    virtual cc::FontAtlas* newFontAtlas() override { return cc::IntrusivePtr{new cc::FontAtlas(this)}.detach(); }
#else
    virtual cc::IntrusivePtr<cc::FontAtlas> createFontAtlas() override { return cc::IntrusivePtr{new cc::FontAtlas(*this)}.detach(); }
#endif
    cc::FontAtlas* resetFontAtlas(cc::FontAtlas* fontAtlas)
    {
        if (_fontAtlas != fontAtlas)
        {
            CC_SAFE_RELEASE(_fontAtlas);
            _fontAtlas = fontAtlas;
        }
        return _fontAtlas;
    }
    cc::FontAtlas* getFontAtlas() const { return _fontAtlas; }
    void releaseAtlas() { resetFontAtlas(nullptr); }
    void setFontSize(float fontSize) {}
    int getOriginalFontSize()const { return _originalFontSize; }
    bool isResizable() { return _resizable; }
    bool canTint() { return _canTint; }

private:
    float _originalFontSize;
    bool _resizable;
    bool _canTint;
    cc::FontAtlas* _fontAtlas;

    friend class UIPackage;
};

NS_FGUI_END

#endif