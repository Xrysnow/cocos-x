#ifndef __GTWEEN_H__
#define __GTWEEN_H__

#include "FairyGUIMacros.h"
#include "cocos2d.h"
#include "GTweener.h"
#include "EaseType.h"
#include "TweenValue.h"
#include "TweenPropType.h"

NS_FGUI_BEGIN

class GTween
{
public:
    static GTweener* to(float startValue, float endValue, float duration);
    static GTweener* to(const cc::Vec2& startValue, const cc::Vec2& endValue, float duration);
    static GTweener* to(const cc::Vec3& startValue, const cc::Vec3& endValue, float duration);
    static GTweener* to(const cc::Vec4& startValue, const cc::Vec4& endValue, float duration);
    static GTweener* to(const cc::Color4B& startValue, const cc::Color4B& endValue, float duration);
    static GTweener* toDouble(double startValue, double endValue, float duration);
    static GTweener* delayedCall(float delay);
    static GTweener* shake(const cc::Vec2& startValue, float amplitude, float duration);
    static bool isTweening(cc::Ref* target);
    static bool isTweening(cc::Ref* target, TweenPropType propType);
    static void kill(cc::Ref* target);
    static void kill(cc::Ref* target, bool complete);
    static void kill(cc::Ref* target, TweenPropType propType, bool complete);
    static GTweener* getTween(cc::Ref* target);
    static GTweener* getTween(cc::Ref* target, TweenPropType propType);
    static void clean();
};

NS_FGUI_END

#endif
