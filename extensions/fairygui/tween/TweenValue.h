#ifndef __TWEENVALUE_H__
#define __TWEENVALUE_H__

#include "FairyGUIMacros.h"
#include "cocos2d.h"

NS_FGUI_BEGIN

class TweenValue
{
public:
    float x;
    float y;
    float z;
    float w;
    double d;

    TweenValue();

    cc::Vec2 getVec2() const;
    void setVec2(const cc::Vec2& value);
    cc::Vec3 getVec3() const;
    void setVec3(const cc::Vec3& value);
    cc::Vec4 getVec4() const;
    void setVec4(const cc::Vec4& value);
    cc::Color4B getColor() const;
    void setColor(const cc::Color4B& value);
    float operator[] (int index) const;
    float& operator[] (int index);
    void setZero();
};

NS_FGUI_END

#endif
