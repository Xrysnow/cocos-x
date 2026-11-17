#ifndef __FUISPRITE_H__
#define __FUISPRITE_H__

#include "cocos2d.h"
#include "FairyGUIMacros.h"

NS_FGUI_BEGIN

class FUISprite : public cc::Sprite
{
public:
    FUISprite();
    virtual ~FUISprite();

    CREATE_FUNC(FUISprite);

    void clearContent();
    void setScale9Grid(cc::Rect* value);
    void setGrayed(bool value);

    FillMethod getFillMethod() const { return _fillMethod; }
    void setFillMethod(FillMethod value);

    FillOrigin getFillOrigin() const { return _fillOrigin; }
    void setFillOrigin(FillOrigin value);

    bool isFillClockwise() const { return _fillClockwise; }
    void setFillClockwise(bool value);

    float getFillAmount() const { return _fillAmount; }
    void setFillAmount(float value);

    bool isScaleByTile() const { return _scaleByTile; }
    void setScaleByTile(bool value);

    virtual void setContentSize(const cc::Size& size) override;

protected:
    virtual void draw(cc::Renderer *renderer, const cc::Mat4 &transform, uint32_t flags) override;

    cc::Tex2F textureCoordFromAlphaPoint(cc::Vec2 alpha);
    cc::Vec3 vertexFromAlphaPoint(cc::Vec2 alpha);
    void updateBar(void);
    void updateRadial(void);
    virtual void updateColor(void) override;
    cc::Vec2 boundaryTexCoord(char index);

    void setupFill();

private:
    FillMethod _fillMethod;
    FillOrigin _fillOrigin;
    float _fillAmount;
    bool _fillClockwise;
    bool _scaleByTile;
    int _vertexDataCount;
    cc::TrianglesCommand::Triangles _fillTriangles;
    cc::V3F_C4B_T2F *_vertexData;
    unsigned short *_vertexIndex;
    
    static cc::Texture2D* _empty;
};

NS_FGUI_END

#endif
