#ifndef __TWEENMANAGER_H__
#define __TWEENMANAGER_H__

#include "FairyGUIMacros.h"
#include "TweenPropType.h"
#include "cocos2d.h"

NS_FGUI_BEGIN

class GTweener;

class TweenManager
{
public:
    static cc::IntrusivePtr<GTweener> createTween();
    static bool isTweening(cc::Ref* target, TweenPropType propType);
    static bool killTweens(cc::Ref* target, TweenPropType propType, bool completed);
    static GTweener* getTween(cc::Ref* target, TweenPropType propType);
    static void update(float dt);
    static void clean();
    static void init();

private:
    static void reset(cc::EventCustom*);

    static GTweener** _activeTweens;
    static std::vector<GTweener*> _tweenerPool;
    static int _totalActiveTweens;
    static int _arrayLength;
    static bool _inited;
};

NS_FGUI_END

#endif
