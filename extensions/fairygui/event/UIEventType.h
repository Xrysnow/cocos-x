#ifndef __UIEVENTTYPE_H__
#define __UIEVENTTYPE_H__

#include "FairyGUIMacros.h"

NS_FGUI_BEGIN

class UIEventType
{
public:
    static constexpr int Enter = 0;
    static constexpr int Exit = 1;
    static constexpr int Changed = 2;
    static constexpr int Submit = 3;

    static constexpr int TouchBegin = 10;
    static constexpr int TouchMove = 11;
    static constexpr int TouchEnd = 12;
    static constexpr int Click = 13;
    static constexpr int RollOver = 14;
    static constexpr int RollOut = 15;
    static constexpr int MouseWheel = 16;
    static constexpr int RightClick = 17;
    static constexpr int MiddleClick = 18;

    static constexpr int PositionChange = 20;
    static constexpr int SizeChange = 21;

    static constexpr int KeyDown = 30;
    static constexpr int KeyUp = 31;

    static constexpr int Scroll = 40;
    static constexpr int ScrollEnd = 41;
    static constexpr int PullDownRelease = 42;
    static constexpr int PullUpRelease = 43;

    static constexpr int ClickItem = 50;
    static constexpr int ClickLink = 51;
    static constexpr int ClickMenu = 52;
    static constexpr int RightClickItem = 53;

    static constexpr int DragStart = 60;
    static constexpr int DragMove = 61;
    static constexpr int DragEnd = 62;
    static constexpr int Drop = 63;

    static constexpr int GearStop = 70;
};

NS_FGUI_END

#endif
