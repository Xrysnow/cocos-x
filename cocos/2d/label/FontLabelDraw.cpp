#include "2d/Label.h"
#include "FontLabelState.h"
#include "LabelLetter.h"
#include "base/Director.h"
#include "renderer/Renderer.h"
#include "renderer/backend/ProgramState.h"

namespace cc
{
namespace
{
struct GlyphQuad
{
    font::GlyphAtlas::Lease slot;
    V3F_C4B_T2F_Quad quad;
};
struct GlyphBatch
{
    TrianglesCommand command;
    cc::IntrusivePtr<backend::ProgramState> program;
    std::vector<V3F_C4B_T2F> vertices;
    std::vector<unsigned short> indices;
    std::vector<font::GlyphAtlas::Lease> slots;
};
}  // namespace
void Label::drawFileText(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    auto& state = *_fileState;
    if (_lengthOfString <= 0 || !_programState || !renderer->isFrameActive())
        return;
    auto& service = *_director->getFontRendering()._service;
    if (_glyphPolicy == GlyphRenderPolicy::Synchronous &&
        std::any_of(state.keys.begin(), state.keys.end(), [&](const auto& key) { return !service.resolve(key); }))
        service.prepare(*renderer, state.keys);
    std::vector<GlyphQuad> glyphs;
    std::vector<font::GlyphKey> missing;
    const int rasterSize = font::selectRasterPpem(_rasterMode, state.ppem);
    const float factor   = float(state.ppem) / rasterSize / state.scale;
    for (int i = 0; i < _lengthOfString; ++i)
    {
        const auto& info = _lettersInfo[i];
        if (!info.valid)
            continue;
        const auto key = state.face->key(info.utf32Char, _rasterMode, state.ppem);
        auto slot      = service.resolve(key);
        if (!slot)
        {
            missing.push_back(key);
            continue;
        }
        if (!slot->page)
            continue;
        const auto& def     = _fontAtlas->_letterDefinitions.at(info.utf32Char);
        const auto& r       = slot->rect;
        const float originX = info.positionX + _linesOffsetX[info.lineIndex];
        const float originY = info.positionY + _letterOffsetY;
        const float left    = originX - def.offsetX / state.scale + slot->left * factor;
        const float top     = originY + (def.offsetY - state.metrics.ascent) / state.scale + slot->top * factor;
        float y1 = top - (r.h - 2) * factor, y2 = top;
        float x1 = left, x2 = left + (r.w - 2) * factor;
        if (_labelWidth > 0 && _overflow == Overflow::CLAMP)
        {
            x1 = std::max(x1, 0.f);
            x2 = std::min(x2, _contentSize.width);
            if (x1 >= x2)
                continue;
        }
        if (_labelHeight > 0)
        {
            y1 = std::max(y1, _tailoredBottomY);
            y2 = std::min(y2, _tailoredTopY);
            if (y1 >= y2)
                continue;
        }
        const float u1 = (r.x + 1 + (x1 - left) / factor) / 2048.f;
        const float u2 = (r.x + 1 + (x2 - left) / factor) / 2048.f;
        const float v1 = (r.y + 1 + (top - y2) / factor) / 2048.f, v2 = (r.y + 1 + (top - y1) / factor) / 2048.f;
        V3F_C4B_T2F_Quad q;
        q.tl.vertices  = {x1, y2, 0};
        q.tr.vertices  = {x2, y2, 0};
        q.bl.vertices  = {x1, y1, 0};
        q.br.vertices  = {x2, y1, 0};
        q.tl.texCoords = {u1, v1};
        q.tr.texCoords = {u2, v1};
        q.bl.texCoords = {u1, v2};
        q.br.texCoords = {u2, v2};
        Color4B tint(_displayedColor, _displayedOpacity);
        if (auto it = _letters.find(i); it != _letters.end())
        {
            auto* letter = static_cast<LabelLetter*>(it->second);
            if (!letter->isVisible())
                continue;
            letter->bind(slot, {def.width, def.height});
            const auto& matrix = letter->getNodeToParentTransform();
            for (auto* v : {&q.bl, &q.br, &q.tr, &q.tl})
            {
                v->vertices.x -= originX;
                v->vertices.y -= originY - def.height;
                matrix.transformPoint(&v->vertices);
            }
            const auto color = letter->getColor();
            tint             = {
                uint8_t(tint.r * color.r / 255),
                uint8_t(tint.g * color.g / 255),
                uint8_t(tint.b * color.b / 255),
                uint8_t(tint.a * letter->getOpacity() / 255)};
        }
        q.tl.colors = q.tr.colors = q.bl.colors = q.br.colors = tint;
        glyphs.push_back({std::move(slot), q});
    }
    if (!missing.empty() && state.visible.poll().status != GlyphStatus::Pending)
        state.visible = service.submit(missing, font::Priority::Visible);
    if (glyphs.empty())
        return;
    const auto projection = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto pass             = [&](Color4F color, float offset, bool glow, const Mat4& mv, Vec2 shift) {
        for (size_t start = 0; start < glyphs.size();)
        {
            auto batch        = std::make_shared<GlyphBatch>();
            auto* texture     = glyphs[start].slot->page->texture.get();
            const float range = glyphs[start].slot->range;
            for (; start < glyphs.size() && glyphs[start].slot->page->texture.get() == texture &&
                   batch->slots.size() < 8192;
                 ++start)
            {
                const auto& g   = glyphs[start];
                const auto base = static_cast<unsigned short>(batch->vertices.size());
                for (auto v : {g.quad.tl, g.quad.bl, g.quad.tr, g.quad.br})
                {
                    v.vertices.x += shift.x;
                    v.vertices.y += shift.y;
                    batch->vertices.push_back(v);
                }
                for (int idx : {0, 1, 2, 3, 2, 1})
                    batch->indices.push_back(static_cast<unsigned short>(base + idx));
                batch->slots.push_back(g.slot);
            }
            batch->program = _programState->clone();
            auto& program  = *batch->program;
            program.setUniform(_mvpMatrixLocation, projection.m, sizeof(projection.m));
            program.setUniform(_textColorLocation, &color, sizeof(color));
            Vec4 params{
                float(_rasterMode),
                range > 0 ? std::min(0.49f, offset / (factor * range)) : 0.f,
                glow ? 1.f : 0.f,
                _blendFunc.src == backend::BlendFactor::ONE ? 1.f : 0.f};
            program.setUniform(program.getUniformLocation("u_glyphParams"), &params, sizeof(params));
            program.setTexture(texture->getBackendTexture());
            auto& cmd                                = batch->command;
            cmd.getPipelineDescriptor().programState = batch->program.get();
            cmd.setSkipBatching(true);
            cmd.init(
                _globalZOrder,
                texture,
                _blendFunc,
                {batch->vertices.data(),
                 batch->indices.data(),
                 unsigned(batch->vertices.size()),
                 unsigned(batch->indices.size())},
                mv,
                flags);
            renderer->addOwnedCommand(&cmd, batch);
        }
    };
    if (_shadowEnabled)
        pass(_shadowColor4F, _currLabelEffect == LabelEffect::OUTLINE ? _outlineSize : 0, false, _shadowTransform, {});
    if (_currLabelEffect == LabelEffect::OUTLINE)
        pass(_effectColorF, _outlineSize, false, transform, {});
    if (_currLabelEffect == LabelEffect::GLOW)
    {
        if (_rasterMode == FontRasterMode::Bitmap)
        {
            Color4F glow  = _effectColorF;
            glow.a       *= 0.24f;
            for (int y = -1; y <= 1; ++y)
                for (int x = -1; x <= 1; ++x)
                    if (x || y)
                        pass(glow, 0, false, transform, {float(x), float(y)});
        }
        else
            pass(_effectColorF, 0, true, transform, {});
    }
    pass(_textColorF, 0, false, transform, {});
}
}  // namespace cc
