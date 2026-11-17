#ifndef __GGRAPH_H__
#define __GGRAPH_H__

#include "FairyGUIMacros.h"
#include "GObject.h"
#include "cocos2d.h"

NS_FGUI_BEGIN

class GGraph : public GObject
{
public:
    GGraph();
    virtual ~GGraph();

    CREATE_FUNC(GGraph);

    void drawRect(float aWidth, float aHeight, int lineSize, const cc::Color4F& lineColor, const cc::Color4F& fillColor);
    void drawEllipse(float aWidth, float aHeight, int lineSize, const cc::Color4F& lineColor, const cc::Color4F& fillColor);
    void drawPolygon(int lineSize, const cc::Color4F& lineColor, const cc::Color4F& fillColor, const cc::Vec2* points, int count);
    void drawRegularPolygon(int lineSize, const cc::Color4F& lineColor, const cc::Color4F& fillColor, int sides, float startAngle = 0, const float* distances = nullptr, int distanceCount = 0);
    bool isEmpty() const { return _type == 0; }

    cc::Color3B getColor() const;
    void setColor(const cc::Color3B& value);

    virtual cc::Value getProp(ObjectPropID propId) override;
    virtual void setProp(ObjectPropID propId, const cc::Value& value) override;

protected:
    virtual void handleInit() override;
    virtual void setup_beforeAdd(ByteBuffer* buffer, int beginPos) override;
    virtual void handleSizeChanged() override;

private:
    void updateShape();

    int _type;
    cc::Color4F _lineColor;
    cc::Color4F _fillColor;
    int _lineSize;
    float* _cornerRadius;
    std::vector<cc::Vec2>* _polygonPoints;
    float _polygonPointOffset;
    int _sides;
    float _startAngle;
    std::vector<float>* _distances;

    cc::DrawNode* _shape;
};

NS_FGUI_END

#endif
