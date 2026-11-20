#ifndef __FUICONTAINER_H__
#define __FUICONTAINER_H__

#include "cocos2d.h"
#include "FairyGUIMacros.h"

NS_FGUI_BEGIN

class GObject;

class RectClippingSupport
{
public:
    RectClippingSupport();

    cc::Rect _clippingRegion;
    bool _clippingEnabled;
    bool _scissorOldState;
    cc::Rect _clippingOldRect;
    cc::Rect _clippingRect;
    bool _clippingRectDirty;

#if !defined(CC_VERSION)
    cc::GroupCommand _groupCommand;
#endif
    //cocos2d::CallbackCommand _beforeVisitCmdScissor;
    //cocos2d::CallbackCommand _afterVisitCmdScissor;
};

class StencilClippingSupport
{
public:
    StencilClippingSupport();

    cc::Node* _stencil;
    cc::StencilStateManager* _stencilStateManager;
#if !defined(CC_VERSION) 
    cc::GroupCommand _groupCommand;
#endif
    //cocos2d::CallbackCommand _beforeVisitCmd;
    //cocos2d::CallbackCommand _afterDrawStencilCmd;
    //cocos2d::CallbackCommand _afterVisitCmd;
};

class FUIContainer : public cc::Node
{
public:
    FUIContainer();
    virtual ~FUIContainer();

    CREATE_FUNC(FUIContainer);

    bool isClippingEnabled() const;
    void setClippingEnabled(bool value);
    const cc::Rect& getClippingRegion() const;
    void setClippingRegion(const cc::Rect& clippingRegion);

    cc::Node* getStencil() const;
    void setStencil(cc::Node* stencil);
    float getAlphaThreshold() const;
    void setAlphaThreshold(float alphaThreshold);
    bool isInverted() const;
    void setInverted(bool inverted);

    void onEnter() override;
    void onEnterTransitionDidFinish() override;
    void onExitTransitionDidStart() override;
    void onExit() override;
    void visit(cc::Renderer *renderer, const cc::Mat4 &parentTransform, uint32_t parentFlags) override;
    void setCameraMask(unsigned short mask, bool applyChildren = true) override;
    void setGlobalZOrder(float globalZOrder) override;

    GObject* gOwner;
private:
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
    const cc::Rect& getClippingRect();

    RectClippingSupport* _rectClippingSupport;
    StencilClippingSupport* _stencilClippingSupport;
    
};

//internal use
class FUIInnerContainer : public cc::Node
{
public:
    CREATE_FUNC(FUIInnerContainer);

    void setPosition2(const cc::Vec2 &position) { setPosition(position.x, _parent->getContentSize().height - position.y); }
    cc::Vec2 getPosition2() { return cc::Vec2(_position.x, _parent->getContentSize().height - _position.y); }
    void setPosition2(float x, float y) { setPosition(x, _parent->getContentSize().height - y); }
    void  setPositionY2(float y) { setPositionY(_parent->getContentSize().height - y); }
    float getPositionY2(void) const { return  _parent->getContentSize().height - _position.y; }
};

NS_FGUI_END

#endif
