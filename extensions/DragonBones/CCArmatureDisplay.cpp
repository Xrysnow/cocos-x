#include "CCArmatureDisplay.h"
#include "CCSlot.h"

DRAGONBONES_NAMESPACE_BEGIN

cc::IntrusivePtr<CCArmatureDisplay> CCArmatureDisplay::create()
{
    cc::IntrusivePtr displayContainer{new CCArmatureDisplay()};
    if (!(displayContainer->init()))
    {
        return nullptr;
    }

    return displayContainer;
}

void CCArmatureDisplay::dbInit(Armature* armature)
{
    _armature = armature;
}

void CCArmatureDisplay::dbClear()
{
    setEventDispatcher(cc::Director::getInstance()->getEventDispatcher());

    _armature = nullptr;
    CC_SAFE_RELEASE(_dispatcher);
    release();
}

void CCArmatureDisplay::dispose(bool disposeProxy)
{
    if (_armature != nullptr)
    {
        _armature->dispose();
        _armature = nullptr;
    }
}

void CCArmatureDisplay::dbUpdate()
{
    const auto drawed = DragonBones::debugDraw;
    if (drawed || _debugDraw)
    {
        _debugDraw = drawed;
        if (_debugDraw)
        {}
        else
        {
            // TODO
        }
    }
}

void CCArmatureDisplay::addDBEventListener(std::string_view type, const std::function<void(EventObject*)>& callback)
{
    auto lambda = [callback](cc::EventCustom* event) -> void {
        callback(static_cast<EventObject*>(event->getUserData()));
    };
    _dispatcher->addCustomEventListener(type, lambda);
}

void CCArmatureDisplay::dispatchDBEvent(std::string_view type, EventObject* value)
{
    _dispatcher->dispatchCustomEvent(type, value);
}

void CCArmatureDisplay::removeDBEventListener(std::string_view type, const std::function<void(EventObject*)>& callback)
{
    // TODO
    _dispatcher->removeCustomEventListeners(type);
}

cc::Rect CCArmatureDisplay::getBoundingBox() const
{
    auto isFirst = true;
    float minX   = 0.0f;
    float minY   = 0.0f;
    float maxX   = 0.0f;
    float maxY   = 0.0f;

    for (const auto slot : _armature->getSlots())
    {
        if (!slot->getVisible() || !slot->getDisplay())
        {
            continue;
        }

        const auto display = static_cast<CCSlot*>(slot)->getCCDisplay();
        const auto bounds  = display->getBoundingBox();
        if (isFirst)
        {
            isFirst = false;
            minX    = bounds.getMinX();
            minY    = bounds.getMinY();
            maxX    = bounds.getMaxX();
            maxY    = bounds.getMaxY();
        }
        else
        {
            minX = std::min(minX, bounds.getMinX());
            minY = std::min(minY, bounds.getMinY());
            maxX = std::max(maxX, bounds.getMaxX());
            maxY = std::max(maxY, bounds.getMaxY());
        }
    }

    cc::Rect rect(minX, minY, maxX - minX, maxY - minY);

    return cc::RectApplyTransform(rect, getNodeToParentTransform());
}

cc::IntrusivePtr<DBCCSprite> DBCCSprite::create()
{
    cc::IntrusivePtr sprite{new DBCCSprite()};

    if (!(sprite->init()))
    {
        return nullptr;
    }

    return sprite;
}

bool DBCCSprite::_checkVisibility(const cc::Mat4& transform, const cc::Size& size, const cc::Rect& rect)
{
    auto scene = cc::Director::getInstance()->getRunningScene();

    // If draw to Rendertexture, return true directly.
    //  only cull the default camera. The culling algorithm is valid for default camera.
    if (!scene || (scene && scene->getDefaultCamera() != cc::Camera::getVisitingCamera()))
        return true;

    auto director = cc::Director::getInstance();
    cc::Rect visiableRect(director->getVisibleOrigin(), director->getVisibleSize());

    // transform center point to screen space
    float hSizeX = size.width / 2;
    float hSizeY = size.height / 2;

    cc::Vec3 v3p(hSizeX, hSizeY, 0);

    transform.transformPoint(&v3p);
    cc::Vec2 v2p = cc::Camera::getVisitingCamera()->projectGL(v3p);

    // convert content size to world coordinates
    float wshw = std::max(fabsf(hSizeX * transform.m[0] + hSizeY * transform.m[4]),
                          fabsf(hSizeX * transform.m[0] - hSizeY * transform.m[4]));
    float wshh = std::max(fabsf(hSizeX * transform.m[1] + hSizeY * transform.m[5]),
                          fabsf(hSizeX * transform.m[1] - hSizeY * transform.m[5]));

    // enlarge visible rect half size in screen coord
    visiableRect.origin.x -= wshw;
    visiableRect.origin.y -= wshh;
    visiableRect.size.width += wshw * 2;
    visiableRect.size.height += wshh * 2;
    bool ret = visiableRect.containsPoint(v2p);
    return ret;
}

void DBCCSprite::draw(cc::Renderer* renderer, const cc::Mat4& transform, uint32_t flags)
{
#if CC_USE_CULLING
    const auto& rect = _polyInfo.getRect();

    // Don't do calculate the culling if the transform was not updated
    auto visitingCamera = cc::Camera::getVisitingCamera();
    auto defaultCamera  = cc::Camera::getDefaultCamera();
    if (visitingCamera == defaultCamera)
    {
        _insideBounds = ((flags & FLAGS_TRANSFORM_DIRTY) || visitingCamera->isViewProjectionUpdated())
                            ? _checkVisibility(transform, _contentSize, rect)
                            : _insideBounds;
    }
    else
    {
        _insideBounds = _checkVisibility(transform, _contentSize, rect);
    }

    if (_insideBounds)
#endif
    {
        _trianglesCommand.init(_globalZOrder, _texture.get(), _blendFunc, _polyInfo.triangles, transform, flags);
        renderer->addCommand(&_trianglesCommand);

#if CC_SPRITE_DEBUG_DRAW
        _debugDrawNode->clear();
        auto count   = _polyInfo.triangles.indexCount / 3;
        auto indices = _polyInfo.triangles.indices;
        auto verts   = _polyInfo.triangles.verts;
        for (ssize_t i = 0; i < count; i++)
        {
            // draw 3 lines
            auto from = verts[indices[i * 3]].vertices;
            auto to   = verts[indices[i * 3 + 1]].vertices;
            _debugDrawNode->drawLine(cc::Vec2(from.x, from.y), cc::Vec2(to.x, to.y), cc::Color4F::WHITE);

            from = verts[indices[i * 3 + 1]].vertices;
            to   = verts[indices[i * 3 + 2]].vertices;
            _debugDrawNode->drawLine(cc::Vec2(from.x, from.y), cc::Vec2(to.x, to.y), cc::Color4F::WHITE);

            from = verts[indices[i * 3 + 2]].vertices;
            to   = verts[indices[i * 3]].vertices;
            _debugDrawNode->drawLine(cc::Vec2(from.x, from.y), cc::Vec2(to.x, to.y), cc::Color4F::WHITE);
        }
#endif  // CC_SPRITE_DEBUG_DRAW
    }
}

cc::PolygonInfo& DBCCSprite::getPolygonInfoModify()
{
    return _polyInfo;
}

DRAGONBONES_NAMESPACE_END
