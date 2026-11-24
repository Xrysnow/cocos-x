/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#pragma once
#include "2d/Sprite.h"
#include "base/Director.h"
#include "2d/font/internal/GlyphAtlas.h"
#include "renderer/TextureAtlas.h"

NS_CC_BEGIN
/**
 * LabelLetter used to update the quad in texture atlas without SpriteBatchNode.
 */
class LabelLetter : public Sprite
{
public:
    LabelLetter()
    {
        _textureAtlas  = nullptr;
        _letterVisible = true;
    }

    static cc::IntrusivePtr<LabelLetter> createWithTexture(Texture2D* texture, const Rect& rect, bool rotated = false)
    {
        cc::IntrusivePtr letter{new LabelLetter()};
        if (letter->initWithTexture(texture, rect, rotated))
        {
            letter->Sprite::setVisible(false);
            return letter;
        }
        return nullptr;
    }

    CREATE_FUNC(LabelLetter);

    void bind(const font::GlyphAtlas::Lease& slot, Size logicalSize)
    {
        if (_slot.lock() == slot)
            return;
        _unbind = std::make_shared<std::function<void()>>([this] { setTexture(nullptr); });
        _slot   = slot;
        std::erase_if(slot->bindings, [](const auto& weak) { return weak.expired(); });
        slot->bindings.emplace_back(_unbind);
        setTexture(slot->page->texture.get());
        const auto& r = slot->rect;
        float scale   = CC_CONTENT_SCALE_FACTOR();
        setTextureRect({(r.x + 1) / scale, (r.y + 1) / scale, (r.w - 2) / scale, (r.h - 2) / scale});
        setContentSize(logicalSize);
    }

    virtual void updateTransform() override
    {
        if (isDirty())
        {
            _transformToBatch = getNodeToParentTransform();
            Vec2& size        = _rect.size;

            float x1 = _offsetPosition.x;
            float y1 = _offsetPosition.y;
            float x2 = x1 + size.width;
            float y2 = y1 + size.height;

            // issue #17022: don't flip, again, the letter since they are flipped in sprite's code
            // if (_flippedX) std::swap(x1, x2);
            // if (_flippedY) std::swap(y1, y2);

            float x = _transformToBatch.m[12];
            float y = _transformToBatch.m[13];

            float cr  = _transformToBatch.m[0];
            float sr  = _transformToBatch.m[1];
            float cr2 = _transformToBatch.m[5];
            float sr2 = -_transformToBatch.m[4];
            float ax  = x1 * cr - y1 * sr2 + x;
            float ay  = x1 * sr + y1 * cr2 + y;

            float bx = x2 * cr - y1 * sr2 + x;
            float by = x2 * sr + y1 * cr2 + y;
            float cx = x2 * cr - y2 * sr2 + x;
            float cy = x2 * sr + y2 * cr2 + y;
            float dx = x1 * cr - y2 * sr2 + x;
            float dy = x1 * sr + y2 * cr2 + y;

            _quad.bl.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(ax), SPRITE_RENDER_IN_SUBPIXEL(ay), _positionZ);
            _quad.br.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(bx), SPRITE_RENDER_IN_SUBPIXEL(by), _positionZ);
            _quad.tl.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(dx), SPRITE_RENDER_IN_SUBPIXEL(dy), _positionZ);
            _quad.tr.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(cx), SPRITE_RENDER_IN_SUBPIXEL(cy), _positionZ);

            if (_textureAtlas)
            {
                _textureAtlas->updateQuad(&_quad, _atlasIndex);
            }

            _recursiveDirty = false;
            setDirty(false);
        }

        Node::updateTransform();
    }

    virtual void updateColor() override
    {
        if (_textureAtlas == nullptr)
        {
            return;
        }

        auto displayedOpacity = _displayedOpacity;
        if (!_letterVisible)
        {
            displayedOpacity = 0.0f;
        }
        Color4B color4(_displayedColor.r, _displayedColor.g, _displayedColor.b, displayedOpacity);
        // special opacity for premultiplied textures
        if (_opacityModifyRGB)
        {
            color4.r *= displayedOpacity / 255.0f;
            color4.g *= displayedOpacity / 255.0f;
            color4.b *= displayedOpacity / 255.0f;
        }
        _quad.bl.colors = color4;
        _quad.br.colors = color4;
        _quad.tl.colors = color4;
        _quad.tr.colors = color4;

        _textureAtlas->updateQuad(&_quad, _atlasIndex);
    }

    void setVisible(bool visible) override
    {
        _letterVisible = visible;
        updateColor();
    }

    bool isVisible() const override { return _letterVisible; }

    // LabelLetter doesn't need to draw directly.
    void draw(Renderer* /*renderer*/, const Mat4& /*transform*/, uint32_t /*flags*/) override {}

private:
    std::weak_ptr<font::GlyphSlot> _slot;
    std::shared_ptr<std::function<void()>> _unbind;
    bool _letterVisible;
};

NS_CC_END
