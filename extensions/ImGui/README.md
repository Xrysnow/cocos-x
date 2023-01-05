# The ImGui extension for axmol
Sync from https://github.com/Xrysnow/cocos2d-x-imgui and do a little changes

## Improvements
* Simplify API, use add/remove renderLoop present ImGui GUI widgets
* Optimize call pipeline flow, support add/remove Node to Scene at ImGui render loop without container iterator damage
* Calculate deltaTime at ```ImGui_ImplCocos2dx_NewFrame``` to avoid error when ```cc.Director``` paused
* Refine ```Init/Shutdown```, Restore all callbacks for glfw to solve recreate ```ImGuiPresenter``` instance support
* Use ```FOURCC``` for key of ImGui render loop
* Add dpi scale support, use ```ImGuiPresenter::getInstance()->scaleAllByDPI(1.0);```
* Easy font manager, stable API ```addFont,removeFont,clearFonts``` to manage ImGui fonts, with ImGui API, very hard to do correctly.

## How to use
```cpp
#include "ImGui/ImGuiPresenter.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameScene : public Scene {
public:
    void onEnter() override
    {
        Scene::onEnter();
        ImGuiPresenter::getInstance()->addFont(R"(C:\Windows\Fonts\msyh.ttc)");
        /* For Simplified Chinese support, please use:
        ImGuiPresenter::getInstance()->addFont(R"(C:\Windows\Fonts\msyh.ttc)", ImGuiPresenter::DEFAULT_FONT_SIZE,
                                           ImGuiPresenter::CHS_GLYPH_RANGE::GENERAL);
        */
        ImGuiPresenter::getInstance()->addRenderLoop("#im01", CC_CALLBACK_0(GameScene::onImGuiDraw, this), this);
    }
    void onExit() override
    {
        Scene::onExit();
        ImGuiPresenter::getInstance()->removeRenderLoop("#im01");
    }
    void onImGuiDraw()
    {
        ImGui::Begin("window");
        ImGui::Text("FPS=%.1f", 1.f / ImGui::GetIO().DeltaTime);
        ImGui::End();
    }
}

```
More about use imgui widgets, please see: https://github.com/ocornut/imgui

## Tested devices
* win32
* macOS

## Known issues
* Can't enable muti-viewports on macOS, so we disable this feature for macOS.

## Other resources of ImGui
* https://github.com/ocornut/imgui/wiki/Bindings
* https://github.com/CedricGuillemet/ImGuizmo
