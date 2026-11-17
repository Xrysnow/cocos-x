#pragma once

#include "cocos2d.h"

class AppDelegate final : public cc::Application
{
public:
    void initGLContextAttrs() override;
    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;
};
