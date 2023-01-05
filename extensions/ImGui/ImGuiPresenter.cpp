#include "ImGuiPresenter.h"
#include <assert.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "imgui_impl_ax_android.h"
#else
    #include "imgui_impl_ax.h"
#endif
#include "imgui_internal.h"

// TODO: mac metal
#if defined(CC_USE_GL)
#    define CC_IMGUI_ENABLE_MULTI_VIEWPORT 1
#else
#    define CC_IMGUI_ENABLE_MULTI_VIEWPORT 0
#endif

NS_CC_EXT_BEGIN

static uint32_t fourccValue(std::string_view str)
{
    if (str.empty() || str[0] != '#')
        return (uint32_t)-1;
    uint32_t value = 0;
    memcpy(&value, str.data() + 1, std::min(sizeof(value), str.size() - 1));
    return value;
}

class ImGuiEventTracker
{
public:
    virtual ~ImGuiEventTracker() {}
};

// Track scene event and check whether routed to the scene graph
class ImGuiSceneEventTracker : public ImGuiEventTracker
{
public:
    bool initWithScene(Scene* scene)
    {
#ifdef CC_PLATFORM_PC
        _trackLayer = utils::newInstance<Node>(&Node::initLayer);

        // note: when at the first click to focus the window, this will not take effect
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [this](Touch* touch, Event*) -> bool { return ImGui::GetIO().WantCaptureMouse; };
        _trackLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, _trackLayer);

        // add by halx99
        auto stopAnyMouse = [=](EventMouse* event) {
            if (ImGui::GetIO().WantCaptureMouse)
            {
                event->stopPropagation();
            }
        };
        auto mouseListener         = EventListenerMouse::create();
        mouseListener->onMouseDown = mouseListener->onMouseUp = stopAnyMouse;
        _trackLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, _trackLayer);
        scene->addChild(_trackLayer, INT_MAX);
#endif
        // add an empty sprite to avoid render problem
        // const auto sp = Sprite::create();
        // sp->setGlobalZOrder(1);
        // sp->setOpacity(0);
        // addChild(sp, 1);

        /*
         * There a 3 choice for schedule frame for ImGui render loop
         * a. at visit/draw to call beginFrame/endFrame, but at ImGui loop, we can't game object and add to Scene
         * directly, will cause damage iterator b. scheduleUpdate at onEnter to call beginFrame, at visit/draw to call
         * endFrame, it's solve iterator damage problem, but when director is paused the director will stop call
         * 'update' function of Scheduler And need modify engine code to call _scheduler->update(_deltaTime) even
         * director is paused, pass 0 for update c. Director::EVENT_BEFORE_DRAW call beginFrame, EVENT_AFTER_VISIT call
         * endFrame
         */

        return true;
    }

    ~ImGuiSceneEventTracker()
    {
#ifdef CC_PLATFORM_PC
        if (_trackLayer)
        {
            if (_trackLayer->getParent())
                _trackLayer->removeFromParent();
            _trackLayer->release();
        }
#endif
    }

private:
    Node* _trackLayer = nullptr;
};

class ImGuiGlobalEventTracker : public ImGuiEventTracker
{
    static const int highestPriority = (std::numeric_limits<int>::min)();

public:
    bool init()
    {
#ifdef CC_PLATFORM_PC
        // note: when at the first click to focus the window, this will not take effect

        auto eventDispatcher = Director::getInstance()->getEventDispatcher();

        _touchListener = utils::newInstance<EventListenerTouchOneByOne>();
        _touchListener->setSwallowTouches(true);
        _touchListener->onTouchBegan = [this](Touch* touch, Event*) -> bool { return ImGui::GetIO().WantCaptureMouse; };
        eventDispatcher->addEventListenerWithFixedPriority(_touchListener, highestPriority);

        // add by halx99
        auto stopAnyMouse = [=](EventMouse* event) {
            if (ImGui::GetIO().WantCaptureMouse)
            {
                event->stopPropagation();
            }
        };
        _mouseListener              = utils::newInstance<EventListenerMouse>();
        _mouseListener->onMouseDown = _mouseListener->onMouseUp = stopAnyMouse;
        eventDispatcher->addEventListenerWithFixedPriority(_mouseListener, highestPriority);
#endif
        return true;
    }

    ~ImGuiGlobalEventTracker()
    {
#ifdef CC_PLATFORM_PC
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        eventDispatcher->removeEventListener(_mouseListener);
        eventDispatcher->removeEventListener(_touchListener);

        _mouseListener->release();
        _touchListener->release();
#endif
    }

    EventListenerTouchOneByOne* _touchListener = nullptr;
    EventListenerMouse* _mouseListener         = nullptr;
};

static ImGuiPresenter* _instance = nullptr;
std::function<void(ImGuiPresenter*)> ImGuiPresenter::_onInit;

ImGuiPresenter* ImGuiPresenter::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new ImGuiPresenter();
        _instance->init();
        if (_onInit)
            _onInit(_instance);
    }
    return _instance;
}

void ImGuiPresenter::destroyInstance()
{
    if (_instance)
    {
        _instance->cleanup();
        delete _instance;
        _instance = nullptr;
    }
}

void ImGuiPresenter::init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking

#if CC_IMGUI_ENABLE_MULTI_VIEWPORT
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport / Platform Windows
#endif
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;
    // io.ConfigViewportsNoDefaultParent = true;
    // io.ConfigDockingAlwaysTabBar = true;
    // io.ConfigDockingTransparentPayload = true;
    // io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T
    // WORK AS EXPECTED. DON'T USE IN USER APP! io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; //
    // FIXME-DPI: Experimental.

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
    // ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding              = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ImGui_ImplAndroid_InitForAx(Director::getInstance()->getOpenGLView(), true);
#else
    auto window = static_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView())->getWindow();
    ImGui_ImplGlfw_InitForAx(window, true);
#endif
    ImGui_ImplAx_Init();

    ImGui_ImplAx_SetCustomFontLoader(&ImGuiPresenter::loadCustomFonts, this);

    ImGui::StyleColorsClassic();

    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addCustomEventListener(Director::EVENT_BEFORE_DRAW, [=](EventCustom*) { beginFrame(); });
    eventDispatcher->addCustomEventListener(Director::EVENT_AFTER_VISIT, [=](EventCustom*) { endFrame(); });
}

void ImGuiPresenter::cleanup()
{
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->removeCustomEventListeners(Director::EVENT_AFTER_VISIT);
    eventDispatcher->removeCustomEventListeners(Director::EVENT_BEFORE_DRAW);

    ImGui_ImplAx_SetCustomFontLoader(nullptr, nullptr);
    ImGui_ImplAx_Shutdown();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ImGui_ImplAndroid_Shutdown();
#else
    ImGui_ImplGlfw_Shutdown();
#endif

    CC_SAFE_RELEASE_NULL(_fontsTexture);

    ImGui::DestroyContext();
}

void ImGuiPresenter::setOnInit(const std::function<void(ImGuiPresenter*)>& callBack)
{
    _onInit = callBack;
}

void ImGuiPresenter::loadCustomFonts(void* ud)
{
    auto thiz = (ImGuiPresenter*)ud;

    auto imFonts = ImGui::GetIO().Fonts;
    imFonts->Clear();

    auto contentZoomFactor = thiz->_contentZoomFactor;
    for (auto& fontInfo : thiz->_fontsInfoMap)
    {
        const ImWchar* imChars = nullptr;
        switch (fontInfo.second.glyphRange)
        {
        case CHS_GLYPH_RANGE::GENERAL:
            imChars = imFonts->GetGlyphRangesChineseSimplifiedCommon();
            break;
        case CHS_GLYPH_RANGE::FULL:
            imChars = imFonts->GetGlyphRangesChineseFull();
            break;
        default:;
        }

        auto fontData = FileUtils::getInstance()->getDataFromFile(fontInfo.first);
        CCASSERT(!fontData.isNull(), "Cannot load font for IMGUI");

        ssize_t bufferSize = 0;
        auto* buffer       = fontData.takeBuffer(&bufferSize);  // Buffer automatically freed by IMGUI

        imFonts->AddFontFromMemoryTTF(buffer, bufferSize, fontInfo.second.fontSize * contentZoomFactor, nullptr,
                                      imChars);
    }
}

float ImGuiPresenter::scaleAllByDPI(float userScale)
{
    float xscale = 1.0f;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    // Gets scale
    glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &xscale, nullptr);
#endif

    auto zoomFactor = userScale * xscale;

    auto imFonts = ImGui::GetIO().Fonts;

    // clear before add new font
    auto fontConf = imFonts->ConfigData;  // copy font config data

    if (zoomFactor != _contentZoomFactor)
    {
        for (auto& fontConf : imFonts->ConfigData)
        {
            fontConf.SizePixels = (fontConf.SizePixels / _contentZoomFactor) * zoomFactor;
        }

        // Destory font informations, let implcocos2dx recreate at newFrame
        ImGui_ImplAx_SetDeviceObjectsDirty();

        ImGui::GetStyle().ScaleAllSizes(zoomFactor);

        _contentZoomFactor = zoomFactor;
    }

    return zoomFactor;
}

void ImGuiPresenter::setViewResolution(float width, float height)
{
    ImGui_ImplAx_SetViewResolution(width, height);
}

void ImGuiPresenter::addFont(std::string_view fontFile, float fontSize, CHS_GLYPH_RANGE glyphRange)
{
    if (FileUtils::getInstance()->isFileExistInternal(fontFile))
    {
        if (_fontsInfoMap.emplace(fontFile, FontInfo{fontSize, glyphRange}).second)
            ImGui_ImplAx_SetDeviceObjectsDirty();
    }
}

void ImGuiPresenter::removeFont(std::string_view fontFile)
{
    auto count = _fontsInfoMap.size();
    _fontsInfoMap.erase(fontFile);
    if (count != _fontsInfoMap.size())
        ImGui_ImplAx_SetDeviceObjectsDirty();
}

void ImGuiPresenter::clearFonts()
{
    bool haveCustomFonts = !_fontsInfoMap.empty();
    _fontsInfoMap.clear();
    if (haveCustomFonts)
        ImGui_ImplAx_SetDeviceObjectsDirty();

    // auto drawData = ImGui::GetDrawData();
    // if(drawData) drawData->Clear();
}

void ImGuiPresenter::end()
{
    _purgeNextLoop = true;
}

/*
 * begin ImGui frame and draw ImGui stubs
 */
void ImGuiPresenter::beginFrame()
{  // drived by event Director::EVENT_BEFORE_DRAW from engine mainLoop
    if (_purgeNextLoop)
    {
        Director::getInstance()->end();
        return;
    }
    if (!_renderPiplines.empty())
    {
        // create frame
        ImGui_ImplAx_NewFrame();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        ImGui_ImplAndroid_NewFrame();
#else
        ImGui_ImplGlfw_NewFrame();
#endif
        ImGui::NewFrame();

        // move to endFrame?
        _fontsTexture = (Texture2D*)ImGui_ImplAx_GetFontsTexture();
        assert(_fontsTexture != nullptr);
        _fontsTexture->retain();

        // draw all gui
        this->update();

        ++_beginFrames;
    }
}

/*
 * flush ImGui draw data to engine
 */
void ImGuiPresenter::endFrame()
{
    if (_beginFrames > 0)
    {
        // render
        ImGui::Render();

        auto drawData = ImGui::GetDrawData();
        if (drawData)
            ImGui_ImplAx_RenderDrawData(drawData);

        ImGui_ImplAx_RenderPlatform();
        --_beginFrames;

        CC_SAFE_RELEASE_NULL(_fontsTexture);
    }
}

void ImGuiPresenter::update()
{
    // clear things from last frame
    usedCCRefIdMap.clear();
    usedCCRef.clear();
    // drawing commands
    for (auto& pipline : _renderPiplines)
        pipline.second.frame();

    // commands will be processed after update
}

bool ImGuiPresenter::addRenderLoop(std::string_view id, std::function<void()> func, Scene* target)
{
    // TODO: check whether exist
    auto fourccId = fourccValue(id);
    if (_renderPiplines.find(fourccId) != _renderPiplines.end())
    {
        return false;
    }

    ImGuiEventTracker* tracker;
    if (target)
        tracker = utils::newInstance<ImGuiSceneEventTracker>(&ImGuiSceneEventTracker::initWithScene, target);
    else
        tracker = utils::newInstance<ImGuiGlobalEventTracker>();

    if (tracker)
    {
        _renderPiplines.emplace(fourccId, RenderPipline{tracker, std::move(func)});
        return true;
    }
    return false;
}

void ImGuiPresenter::removeRenderLoop(std::string_view id)
{
    auto fourccId   = fourccValue(id);
    const auto iter = _renderPiplines.find(fourccId);
    if (iter != _renderPiplines.end())
    {
        auto tracker = iter->second.tracker;
        delete tracker;
        _renderPiplines.erase(iter);
    }

    if (_renderPiplines.empty())
        deactiveImGuiViewports();
}

void ImGuiPresenter::deactiveImGuiViewports()
{
    ImGuiContext& g = *GImGui;
    if (!(g.ConfigFlagsCurrFrame & ImGuiConfigFlags_ViewportsEnable))
        return;

    // Create/resize/destroy platform windows to match each active viewport.
    // Skip the main viewport (index 0), which is always fully handled by the application!
    for (int i = 1; i < g.Viewports.Size; i++)
    {
        ImGuiViewportP* viewport = g.Viewports[i];
        viewport->Window->Active = false;
    }
}

static std::tuple<ImVec2, ImVec2> getTextureUV(Sprite* sp)
{
    ImVec2 uv0, uv1;
    if (!sp || !sp->getTexture())
        return std::tuple<ImVec2, ImVec2>{uv0, uv1};
    const auto& rect        = sp->getTextureRect();
    const auto tex          = sp->getTexture();
    const float atlasWidth  = (float)tex->getPixelsWide();
    const float atlasHeight = (float)tex->getPixelsHigh();
    uv0.x                   = rect.origin.x / atlasWidth;
    uv0.y                   = rect.origin.y / atlasHeight;
    uv1.x                   = (rect.origin.x + rect.size.width) / atlasWidth;
    uv1.y                   = (rect.origin.y + rect.size.height) / atlasHeight;
    return std::tuple<ImVec2, ImVec2>{uv0, uv1};
}

void ImGuiPresenter::image(Texture2D* tex,
                     const ImVec2& size,
                     const ImVec2& uv0,
                     const ImVec2& uv1,
                     const ImVec4& tint_col,
                     const ImVec4& border_col)
{
    if (!tex)
        return;
    auto size_ = size;
    if (size_.x <= 0.f)
        size_.x = tex->getPixelsWide();
    if (size_.y <= 0.f)
        size_.y = tex->getPixelsHigh();
    ImGui::PushID(getCCRefId(tex));
    ImGui::Image((ImTextureID)tex, size_, uv0, uv1, tint_col, border_col);
    ImGui::PopID();
}

void ImGuiPresenter::image(Sprite* sprite, const ImVec2& size, const ImVec4& tint_col, const ImVec4& border_col)
{
    if (!sprite || !sprite->getTexture())
        return;
    auto size_       = size;
    const auto& rect = sprite->getTextureRect();
    if (size_.x <= 0.f)
        size_.x = rect.size.width;
    if (size_.y <= 0.f)
        size_.y = rect.size.height;
    ImVec2 uv0, uv1;
    std::tie(uv0, uv1) = getTextureUV(sprite);
    ImGui::PushID(getCCRefId(sprite));
    ImGui::Image((ImTextureID)sprite->getTexture(), size_, uv0, uv1, tint_col, border_col);
    ImGui::PopID();
}

bool ImGuiPresenter::imageButton(Texture2D* tex,
                           const ImVec2& size,
                           const ImVec2& uv0,
                           const ImVec2& uv1,
                           int frame_padding,
                           const ImVec4& bg_col,
                           const ImVec4& tint_col)
{
    if (!tex)
        return false;
    auto size_ = size;
    if (size_.x <= 0.f)
        size_.x = tex->getPixelsWide();
    if (size_.y <= 0.f)
        size_.y = tex->getPixelsHigh();
    ImGui::PushID(getCCRefId(tex));
    const auto ret = ImGui::ImageButton((ImTextureID)tex, size_, uv0, uv1, frame_padding, bg_col, tint_col);
    ImGui::PopID();
    return ret;
}

bool ImGuiPresenter::imageButton(Sprite* sprite,
                           const ImVec2& size,
                           int frame_padding,
                           const ImVec4& bg_col,
                           const ImVec4& tint_col)
{
    if (!sprite || !sprite->getTexture())
        return false;
    auto size_       = size;
    const auto& rect = sprite->getTextureRect();
    if (size_.x <= 0.f)
        size_.x = rect.size.width;
    if (size_.y <= 0.f)
        size_.y = rect.size.height;
    ImVec2 uv0, uv1;
    std::tie(uv0, uv1) = getTextureUV(sprite);
    ImGui::PushID(getCCRefId(sprite));
    const auto ret =
        ImGui::ImageButton((ImTextureID)sprite->getTexture(), size_, uv0, uv1, frame_padding, bg_col, tint_col);
    ImGui::PopID();
    return ret;
}

void ImGuiPresenter::node(Node* node, const ImVec4& tint_col, const ImVec4& border_col)
{
    if (!node)
        return;
    const auto size = node->getContentSize();
    const auto pos  = ImGui::GetCursorScreenPos();
    Mat4 tr;
    tr.m[5]  = -1;
    tr.m[12] = pos.x;
    tr.m[13] = pos.y + size.height;
    if (border_col.w > 0.f)
    {
        tr.m[12] += 1;
        tr.m[13] += 1;
    }
    node->setNodeToParentTransform(tr);
    ImGui::PushID(getCCRefId(node));
    ImGui::Image((ImTextureID)node, ImVec2(size.width, size.height), ImVec2(0, 0), ImVec2(1, 1), tint_col, border_col);
    ImGui::PopID();
}

bool ImGuiPresenter::nodeButton(Node* node, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)
{
    if (!node)
        return false;
    const auto size = node->getContentSize();
    const auto pos  = ImGui::GetCursorScreenPos();
    Mat4 tr;
    tr.m[5]  = -1;
    tr.m[12] = pos.x;
    tr.m[13] = pos.y + size.height;
    if (frame_padding >= 0)
    {
        tr.m[12] += (float)frame_padding;
        tr.m[13] += (float)frame_padding;
    }
    else
    {
        tr.m[12] += ImGui::GetStyle().FramePadding.x;
        tr.m[13] += ImGui::GetStyle().FramePadding.y;
    }
    node->setNodeToParentTransform(tr);
    ImGui::PushID(getCCRefId(node));
    const auto ret = ImGui::ImageButton((ImTextureID)node, ImVec2(size.width, size.height), ImVec2(0, 0), ImVec2(1, 1),
                                        frame_padding, bg_col, tint_col);
    ImGui::PopID();
    return ret;
}

std::tuple<ImTextureID, int> ImGuiPresenter::useTexture(Texture2D* texture)
{
    if (!texture)
        return std::tuple<ImTextureID, int>{nullptr, 0};
    return std::tuple<ImTextureID, int>{(ImTextureID)texture, getCCRefId(texture)};
}

std::tuple<ImTextureID, ImVec2, ImVec2, int> ImGuiPresenter::useSprite(Sprite* sprite)
{
    if (!sprite || !sprite->getTexture())
        return std::tuple<ImTextureID, ImVec2, ImVec2, int>{nullptr, {}, {}, 0};
    ImVec2 uv0, uv1;
    std::tie(uv0, uv1) = getTextureUV(sprite);
    return std::tuple<ImTextureID, ImVec2, ImVec2, int>{(ImTextureID)sprite->getTexture(), uv0, uv1,
                                                        getCCRefId(sprite)};
}

std::tuple<ImTextureID, ImVec2, ImVec2, int> ImGuiPresenter::useNode(Node* node, const ImVec2& pos)
{
    if (!node)
        return std::tuple<ImTextureID, ImVec2, ImVec2, int>{nullptr, {}, {}, 0};
    const auto size = node->getContentSize();
    Mat4 tr;
    tr.m[5]  = -1;
    tr.m[12] = pos.x;
    tr.m[13] = pos.y + size.height;
    node->setNodeToParentTransform(tr);
    return std::tuple<ImTextureID, ImVec2, ImVec2, int>{
        (ImTextureID)node, pos, ImVec2(pos.x + size.width, pos.y + size.height), getCCRefId(node)};
}

void ImGuiPresenter::setNodeColor(Node* node, const ImVec4& col)
{
    if (node)
    {
        node->setColor({uint8_t(col.x * 255), uint8_t(col.y * 255), uint8_t(col.z * 255)});
        node->setOpacity(uint8_t(col.w * 255));
    }
}

void ImGuiPresenter::setNodeColor(Node* node, ImGuiCol col)
{
    if (node && 0 <= col && col < ImGuiCol_COUNT)
        setNodeColor(node, ImGui::GetStyleColorVec4(col));
}

void ImGuiPresenter::setLabelColor(Label* label, const ImVec4& col)
{
    if (label)
    {
        label->setTextColor({uint8_t(col.x * 255), uint8_t(col.y * 255), uint8_t(col.z * 255), uint8_t(col.w * 255)});
    }
}

void ImGuiPresenter::setLabelColor(Label* label, bool disabled)
{
    if (label)
        setLabelColor(label, ImGui::GetStyleColorVec4(disabled ? ImGuiCol_TextDisabled : ImGuiCol_Text));
}

void ImGuiPresenter::setLabelColor(Label* label, ImGuiCol col)
{
    if (label && 0 <= col && col < ImGuiCol_COUNT)
        setLabelColor(label, ImGui::GetStyleColorVec4(col));
}

ImWchar* ImGuiPresenter::addGlyphRanges(std::string_view key, const std::vector<ImWchar>& ranges)
{
    auto it = glyphRanges.find(key);
    // the pointer must be persistant, do not replace
    if (it != glyphRanges.end())
        return it->second.data();
    it = glyphRanges.emplace(key, ranges).first;  // glyphRanges[key] = ranges;
    if (ranges.empty())
        it->second.push_back(0);
    return it->second.data();
}

void ImGuiPresenter::mergeFontGlyphs(ImFont* dst, ImFont* src, ImWchar start, ImWchar end)
{
    if (!dst || !src || start > end)
        return;
    for (auto i = start; i <= end; ++i)
    {
        const auto g = src->FindGlyphNoFallback(i);
        if (g)
        {
            dst->AddGlyph(nullptr, g->Codepoint, g->X0, g->Y0, g->X1, g->Y1, g->U0, g->V0, g->U1, g->V1, g->AdvanceX);
        }
    }
    dst->BuildLookupTable();
}

int ImGuiPresenter::getCCRefId(Ref* p)
{
    int id        = 0;
    const auto it = usedCCRefIdMap.find(p);
    if (it == usedCCRefIdMap.end())
    {
        usedCCRefIdMap[p] = 0;
        usedCCRef.pushBack(p);
    }
    else
        id = ++it->second;
    // BKDR hash
    constexpr unsigned int seed = 131;
    unsigned int hash           = 0;
    for (auto i = 0u; i < sizeof(void*); ++i)
        hash = hash * seed + ((const char*)&p)[i];
    for (auto i = 0u; i < sizeof(int); ++i)
        hash = hash * seed + ((const char*)&id)[i];
    return (int)hash;
}

NS_CC_EXT_END
