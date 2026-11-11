#pragma once

#include "cocos2d.h"

class AppDelegate final : public cocos2d::Application
{
public:
    void initGLContextAttrs() override;
    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;
};
