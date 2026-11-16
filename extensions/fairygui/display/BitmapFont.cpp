#include "BitmapFont.h"

USING_NS_FGUI;

BitmapFont::BitmapFont():_fontAtlas(nullptr),_originalFontSize(0),_resizable(false)
{
}

BitmapFont::~BitmapFont()
{
}

cc::IntrusivePtr<BitmapFont> BitmapFont::create()
{
    cc::IntrusivePtr font{new BitmapFont()};
    return font;
}

int * BitmapFont::getHorizontalKerningForTextUTF32(const std::u32string & text, int & outNumLetters) const
{
    return nullptr;
}
