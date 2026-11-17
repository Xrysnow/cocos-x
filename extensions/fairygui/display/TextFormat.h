#ifndef __TEXTFORMAT_H__
#define __TEXTFORMAT_H__

#include "cocos2d.h"
#include "FairyGUIMacros.h"

NS_FGUI_BEGIN

class TextFormat
{
public:
    TextFormat();
    TextFormat(const TextFormat & other);
    TextFormat &operator =(const TextFormat & other);

	void setFormat(const TextFormat& format);
    void enableEffect(int effectFlag) { effect |= effectFlag; }
    void disableEffect(int effectFlag) { effect &= ~effectFlag; }
    bool hasEffect(int effectFlag) const { return (effect & effectFlag) != 0; }

    static constexpr int OUTLINE = 1;
    static constexpr int SHADOW = 2;
    static constexpr int GLOW = 4;

    std::string face;
    float fontSize;
    cc::Color3B color;
    bool bold;
    bool italics;
    bool underline;
    int lineSpacing;
    int letterSpacing;
    cc::TextHAlignment align;
    cc::TextVAlignment verticalAlign;

    int effect;
    cc::Color3B outlineColor;
    int outlineSize;
    cc::Color3B shadowColor;
    cc::Size shadowOffset;
    int shadowBlurRadius;
    cc::Color3B glowColor;

    //internal use
    bool _hasColor;
};

NS_FGUI_END

#endif
