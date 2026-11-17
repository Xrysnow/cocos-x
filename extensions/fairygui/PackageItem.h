#ifndef __PACKAGEITEM_H__
#define __PACKAGEITEM_H__

#include "FairyGUIMacros.h"
#include "cocos2d.h"

NS_FGUI_BEGIN

class UIPackage;
class UIObjectFactory;
class GComponent;
class BitmapFont;
class PixelHitTestData;
class ByteBuffer;

class PackageItem : public cc::Ref
{
public:
    PackageItem();
    virtual ~PackageItem();

    void load();
    PackageItem* getBranch();
    PackageItem* getHighResolution();

public:
    UIPackage* owner;

    PackageItemType type;
    ObjectType objectType;
    std::string id;
    std::string name;
    int width;
    int height;
    std::string file;
    ByteBuffer* rawData;
    std::vector<std::string>* branches;
    std::vector<std::string>* highResolution;

    //atlas
    cc::Texture2D* texture;

    //image
    cc::Rect* scale9Grid;
    bool scaleByTile;
    int tileGridIndice;
    cc::SpriteFrame* spriteFrame;
    PixelHitTestData* pixelHitTestData;

    //movieclip
    cc::Animation* animation;
    float delayPerUnit;
    float repeatDelay;
    bool swing;

    //component
    std::function<cc::IntrusivePtr<GComponent>()> extensionCreator;
    bool translated;

    //font
    BitmapFont* bitmapFont;

    //skeleton
    cc::Vec2* skeletonAnchor;
};

NS_FGUI_END

#endif
