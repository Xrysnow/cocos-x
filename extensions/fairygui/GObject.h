#ifndef __GOBJECT_H__
#define __GOBJECT_H__

#include "Controller.h"
#include "FairyGUIMacros.h"
#include "Relations.h"
#include "cocos2d.h"
#include "event/UIEventDispatcher.h"
#include "gears/GearBase.h"

NS_FGUI_BEGIN

class GComponent;
class GGroup;
class ByteBuffer;
class GRoot;
class PackageItem;
class GTreeNode;

class GObject : public UIEventDispatcher
{
public:
    static GObject* getDraggingObject() { return _draggingObject; }

    GObject();
    virtual ~GObject();

    CREATE_FUNC(GObject);

    float getX() const { return _position.x; };
    void setX(float value);
    float getY() const { return _position.y; };
    void setY(float value);
    const cc::Vec2& getPosition() const { return _position; }
    void setPosition(float xv, float yv);
    float getXMin() const;
    void setXMin(float value);
    float getYMin() const;
    void setYMin(float value);

    bool isPixelSnapping() const { return _pixelSnapping; }
    void setPixelSnapping(bool value);

    float getWidth() const { return _size.width; }
    void setWidth(float value) { setSize(value, _rawSize.height); }
    float getHeight() const { return _size.height; }
    void setHeight(float value) { setSize(_rawSize.width, value); }
    const cc::Size& getSize() const { return _size; }
    void setSize(float wv, float hv, bool ignorePivot = false);

    void center(bool restraint = false);
    void makeFullScreen();

    const cc::Vec2& getPivot() const { return _pivot; }
    void setPivot(float xv, float yv, bool asAnchor = false);
    bool isPivotAsAnchor() const { return _pivotAsAnchor; }

    float getScaleX() const { return _scale.x; }
    void setScaleX(float value) { setScale(value, _scale.y); }
    float getScaleY() const { return _scale.y; }
    void setScaleY(float value) { setScale(_scale.x, value); }
    const cc::Vec2& getScale() const { return _scale; }
    void setScale(float xv, float yv);

    float getSkewX() const { return _displayObject->getSkewX(); }
    void setSkewX(float value);

    float getSkewY() const { return _displayObject->getSkewY(); }
    void setSkewY(float value);

    float getRotation() const { return _rotation; }
    void setRotation(float value);

    float getAlpha() const { return _alpha; }
    void setAlpha(float value);

    bool isGrayed() const { return _grayed; }
    void setGrayed(bool value);

    bool isVisible() const { return _visible; }
    void setVisible(bool value);

    bool isTouchable() const { return _touchable; }
    void setTouchable(bool value);

    int getSortingOrder() const { return _sortingOrder; }
    void setSortingOrder(int value);

    GGroup* getGroup() const { return _group; }
    void setGroup(GGroup* value);

    virtual const std::string& getText() const;
    virtual void setText(const std::string& text);

    virtual const std::string& getIcon() const;
    virtual void setIcon(const std::string& text);

    const std::string& getTooltips() const { return _tooltips; }
    void setTooltips(const std::string& value);

    void* getData() const { return _data; };
    void setData(void* value) { _data = value; }
    const cc::Value& getCustomData() const { return _customData; }
    void setCustomData(const cc::Value& value) { _customData = value; }

    bool isDraggable() const { return _draggable; }
    void setDraggable(bool value);
    cc::Rect* getDragBounds() const { return _dragBounds; }
    void setDragBounds(const cc::Rect& value);

    void startDrag(int touchId = -1);
    void stopDrag();

    std::string getResourceURL() const;

    PackageItem* getPackageItem() const { return _packageItem; }

    cc::Vec2 globalToLocal(const cc::Vec2& pt);
    cc::Rect globalToLocal(const cc::Rect& rect);
    cc::Vec2 localToGlobal(const cc::Vec2& pt);
    cc::Rect localToGlobal(const cc::Rect& rect);
    cc::Rect transformRect(const cc::Rect& rect, GObject* targetSpace);

    Relations* relations() { return _relations; }
    void addRelation(GObject* target, RelationType relationType, bool usePercent = false);
    void removeRelation(GObject* target, RelationType relationType);

    GearBase* getGear(int index);
    bool checkGearController(int index, GController* c);
    uint32_t addDisplayLock();
    void releaseDisplayLock(uint32_t token);

    GComponent* getParent() const { return _parent; }
    GObject* findParent() const;
    cc::Node* displayObject() const { return _displayObject; }
    GRoot* getRoot() const;
    bool onStage() const;
    void removeFromParent();

    void addClickListener(const EventCallback& callback) { addEventListener(UIEventType::Click, callback); }
    void addClickListener(const EventCallback& callback, const EventTag& tag) { addEventListener(UIEventType::Click, callback, tag); }
    void removeClickListener(const EventTag& tag) { removeEventListener(UIEventType::Click, tag); }

    virtual cc::Value getProp(ObjectPropID propId);
    virtual void setProp(ObjectPropID propId, const cc::Value& value);

    virtual void constructFromResource();
    virtual GObject* hitTest(const cc::Vec2& worldPoint, const cc::Camera* camera);

    template <typename T>
    T* as();

    GTreeNode* treeNode() const { return _treeNode; }

    std::string id;
    std::string name;
    cc::Size sourceSize;
    cc::Size initSize;
    cc::Size minSize;
    cc::Size maxSize;

    //internal use
    bool _underConstruct;
    bool _gearLocked;
    bool _alignToBL;

protected:
    GComponent* _parent;
    cc::Node* _displayObject;
    PackageItem* _packageItem;
    int _sizeImplType;
    bool _touchDisabled;

    virtual void handleInit();
    virtual void handleSizeChanged();
    virtual void handleScaleChanged();
    virtual void handleGrayedChanged();
    virtual void handlePositionChanged();
    virtual void handleControllerChanged(GController* c);
    virtual void handleAlphaChanged();
    virtual void handleVisibleChanged();

    virtual void onEnter();
    virtual void onExit();

    virtual void setup_beforeAdd(ByteBuffer* buffer, int beginPos);
    virtual void setup_afterAdd(ByteBuffer* buffer, int beginPos);

    bool init();

    void updateGear(int index);
    void checkGearDisplay();

    void setSizeDirectly(float wv, float hv);

    cc::Vec2 _position;
    cc::Size _size;
    cc::Size _rawSize;
    cc::Vec2 _pivot;
    cc::Vec2 _scale;
    bool _pivotAsAnchor;
    float _alpha;
    float _rotation;
    bool _visible;
    bool _touchable;
    bool _grayed;
    bool _finalGrayed;

private:
    bool internalVisible() const;
    bool internalVisible2() const;
    bool internalVisible3() const;
    void updateGearFromRelations(int index, float dx, float dy);
    void transformRectPoint(const cc::Vec2& pt, float rect[], GObject* targetSpace);

    void initDrag();
    void dragBegin(int touchId);
    void dragEnd();
    void onTouchBegin(EventContext* context);
    void onTouchMove(EventContext* context);
    void onTouchEnd(EventContext* context);
    void onRollOver(EventContext* context);
    void onRollOut(EventContext* context);

    bool _internalVisible;
    bool _handlingController;
    bool _draggable;
    int _sortingOrder;
    bool _focusable;
    std::string _tooltips;
    bool _pixelSnapping;
    GGroup* _group;
    float _sizePercentInGroup;
    Relations* _relations;
    GearBase* _gears[10];
    void* _data;
    cc::Value _customData;
    cc::Vec2 _dragTouchStartPos;
    cc::Rect* _dragBounds;
    bool _dragTesting;
    GTreeNode* _treeNode;

    uint64_t _uid;
    size_t _weakPtrRef;

    static GObject* _draggingObject;

    friend class GComponent;
    friend class GGroup;
    friend class RelationItem;
    friend class UIObjectFactory;
    friend class WeakPtr;
    friend class UIPackage;
    friend class GTree;
};

template <typename T>
inline T* GObject::as()
{
    return dynamic_cast<T*>(this);
}

NS_FGUI_END

#endif
