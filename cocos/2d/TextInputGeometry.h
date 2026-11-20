#pragma once

#include <algorithm>
#include "2d/Camera.h"
#include "2d/Scene.h"
#include "platform/TextInputTypes.h"

namespace cc
{
// Project the same local geometry used to draw the field into GLView design coordinates.
inline std::optional<TextInputArea> textInputAreaForNode(const Node& node, const Rect& caret, const Rect& line)
{
    auto camera = Camera::getVisitingCamera();
    if (!camera)
    {
        auto scene = node.getScene();
        camera = scene ? scene->getDefaultCamera() : nullptr;
    }
    if (!camera || !(node.getCameraMask() & static_cast<unsigned short>(camera->getCameraFlag())))
        return {};

    const auto world = node.getNodeToWorldTransform();
    auto project = [&](const Rect& rect) {
        Vec2 low, high;
        for (unsigned i = 0; i < 4; ++i)
        {
            Vec3 p(i & 1 ? rect.getMaxX() : rect.getMinX(), i & 2 ? rect.getMaxY() : rect.getMinY(), 0);
            world.transformPoint(&p);
            const auto pt = camera->projectGL(p);
            if (i == 0)
                low = high = pt;
            else
            {
                low.x = std::min(low.x, pt.x);
                low.y = std::min(low.y, pt.y);
                high.x = std::max(high.x, pt.x);
                high.y = std::max(high.y, pt.y);
            }
        }
        return TextInputRect{low.x, low.y, high.x - low.x, high.y - low.y};
    };
    return TextInputArea{project(caret), project(line), {}, TextInputSpace::design};
}
}  // namespace cc
