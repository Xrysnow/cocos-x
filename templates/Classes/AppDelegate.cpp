#include "AppDelegate.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"

using namespace cocos2d;

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs attributes{8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(attributes);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto* director = Director::getInstance();
    auto* view = director->getOpenGLView();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    if (!view)
    {
        view = GLViewImpl::createWithRect("cocos-x Demo", Rect(0, 0, 960, 540));
        if (!view)
            return false;
        director->setOpenGLView(view);
    }
#endif
    // Android and iOS create their native surface before launching the app.
    if (!view)
        return false;

    auto* files = FileUtils::getInstance();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    // Resolve through FileUtils' executable search path as well as the CWD.
    // A relative addSearchPath("Resources") alone only extends its default root.
    const auto script = files->fullPathForFilename("Resources/main.lua");
    if (script.empty())
        return false;
    files->addSearchPath(script.substr(0, script.find_last_of("/\\") + 1), true);
#else
    const auto script = files->fullPathForFilename("main.lua");
    if (script.empty())
        return false;
#endif
    view->setIcon("icon.png");
    view->setDesignResolutionSize(960, 540, ResolutionPolicy::SHOW_ALL);
    director->setAnimationInterval(1.0f / 60.0f);
    director->setDisplayStats(false);

    auto* engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    // The script returns true after installing its scene; missing/broken scripts
    // must fail launch rather than leave an empty window running.
    return engine->executeScriptFile(script.c_str()) == 1;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
