#include "RasterGeometry.h"

namespace cc::font::detail
{
namespace
{
constexpr unsigned palette[]{6, 5, 3};  // Cyan, magenta, yellow.

double splineLength(const Curve& c)
{
    Point previous = c.start();
    double length  = 0;
    for (int i = 1; i <= 4; ++i)
    {
        const Point p  = c.at(i / 4.);
        length        += std::sqrt((p - previous).length2());
        previous       = p;
    }
    return length;
}
}  // namespace

void colorEdges(Contour& contour)
{
    std::vector<size_t> corners;
    const double threshold = std::sin(3.0);
    Point previous         = contour.back().tangent(true);
    for (size_t i = 0; i < contour.size(); ++i)
    {
        const auto dir = contour[i].tangent(false);
        if (dir.dot(previous) <= 0 || std::abs(dir.cross(previous)) > threshold)
            corners.push_back(i);
        previous = contour[i].tangent(true);
    }
    if (corners.empty())
        return;  // White: all three channels carry the same smooth boundary.
    if (corners.size() == 1)
    {
        std::rotate(contour.begin(), contour.begin() + corners.front(), contour.end());
        if (contour.size() < 3)
        {
            Contour split;
            for (const auto& c : contour)
                for (int i = 0; i < 3; ++i)
                    split.push_back(c.section(i / 3., (i + 1) / 3.));
            contour.swap(split);
        }
        const unsigned colors[]{palette[0], 7, palette[1]};
        for (size_t i = 0; i < contour.size(); ++i)
            contour[i].color = colors[(3 * i + 1) / contour.size()];
        return;
    }

    const size_t count = corners.size();
    std::vector<double> lengths(count);
    for (size_t k = 0; k < count; ++k)
    {
        const size_t end = corners[(k + 1) % count];
        for (size_t i = corners[k]; i != end; i = (i + 1) % contour.size())
            lengths[k] += splineLength(contour[i]);
    }
    // Ink-trap coloring: give the short spline between two longer splines
    // the remaining color, so the two major splines stay distinguishable.
    std::vector<unsigned> colors(count);
    std::vector<size_t> major;
    for (size_t k = 0; k < count; ++k)
        if (count <= 3 || lengths[k] >= lengths[(k + 1) % count] || lengths[k] >= lengths[(k + count - 1) % count])
            major.push_back(k);
    for (size_t i = 0; i < major.size(); ++i)
    {
        unsigned color = palette[i % 3];
        if (i && i + 1 == major.size() && color == colors[major.front()])
            color = palette[(i + 1) % 3];
        colors[major[i]] = color;
    }
    for (size_t k = 0; k < count; ++k)
    {
        if (!colors[k])
            for (unsigned candidate : palette)
                if (candidate != colors[(k + 1) % count] && candidate != colors[(k + count - 1) % count])
                {
                    colors[k] = candidate;
                    break;
                }
        const size_t end = corners[(k + 1) % count];
        for (size_t i = corners[k]; i != end; i = (i + 1) % contour.size())
            contour[i].color = colors[k];
    }
}
}  // namespace cc::font::detail
