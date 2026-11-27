#include "RasterGeometry.h"
#include FT_OUTLINE_H

namespace cc::font::detail
{
namespace
{
constexpr int tileSize    = 8;
constexpr double infinity = std::numeric_limits<double>::infinity();

using SdfCandidate = std::pair<double, size_t>;  // Squared tile lower bound, edge index.

void selectSdfTile(std::vector<SdfCandidate>& candidates, std::span<const Edge> edges,
                   const Bounds& tile, double cap2)
{
    candidates.clear();
    for (size_t i = 0; i < edges.size(); ++i)
    {
        const double lower2 = edges[i].bounds.distance2(tile);
        if (lower2 <= cap2)
            candidates.emplace_back(lower2, i);
    }
    std::sort(candidates.begin(), candidates.end());
}

float sampleSdf(std::span<const Edge> edges, std::span<const SdfCandidate> candidates, Point p,
                double cap2, double slack2)
{
    double best2 = cap2;
    const Bounds sample{p, p};
    for (const auto& [tileLower2, index] : candidates)
    {
        if (tileLower2 > best2 + slack2)
            break;
        const auto& edge = edges[index];
        if (edge.bounds.distance2(sample) <= best2 + slack2)
            best2 = std::min(best2, edge.nearestDistance2(p));
    }
    return float(std::sqrt(best2));
}

struct Selector
{
    double nearest{infinity}, alignment{infinity}, pseudo{infinity};
    double negative{-infinity}, positive{infinity};

    void consider(Edge::Hit hit)
    {
        if (std::abs(hit.distance) < std::abs(nearest) ||
            (std::abs(hit.distance) == std::abs(nearest) && hit.alignment < alignment))
        {
            nearest   = hit.distance;
            alignment = hit.alignment;
            pseudo    = hit.pseudo;
        }
    }
    void extend(double d)
    {
        if (d >= 0)
            positive = std::min(positive, d);
        if (d <= 0)
            negative = std::max(negative, d);
    }
    double value() const
    {
        const double extra = nearest < 0 ? negative : positive;
        return std::abs(extra) < std::abs(pseudo) ? extra : pseudo;
    }
};

double upperBound2(Point p, const Bounds& tile)
{
    const double x = std::max(std::abs(p.x - tile.lo.x), std::abs(p.x - tile.hi.x));
    const double y = std::max(std::abs(p.y - tile.lo.y), std::abs(p.y - tile.hi.y));
    return x * x + y * y;
}

bool extensionInRange(Point point, Point direction, Point bisector, const Bounds& tile, double limit)
{
    const double cosine = direction.dot(bisector);
    Bounds endpoint{point, point};
    return cosine <= 0 || endpoint.distance2(tile) * cosine * cosine <= limit;
}

void selectMsdfTile(std::vector<size_t>& indices, std::span<const Edge> edges, const Bounds& tile)
{
    indices.clear();
    std::array<double, 3> upper{infinity, infinity, infinity};
    for (const auto& edge : edges)
    {
        const double bound = std::min(upperBound2(edge.curve.start(), tile), upperBound2(edge.curve.end(), tile));
        for (int c = 0; c < 3; ++c)
            if (edge.curve.color & (1u << c))
                upper[c] = std::min(upper[c], bound);
    }
    for (size_t i = 0; i < edges.size(); ++i)
    {
        const auto& e = edges[i];
        double limit  = 0;
        for (int c = 0; c < 3; ++c)
            if (e.curve.color & (1u << c))
                limit = std::max(limit, upper[c]);
        limit = limit * (1 + 1e-10) + 1e-12;
        if (e.bounds.distance2(tile) <= limit ||
            extensionInRange(e.curve.start(), e.startDir, e.startBisector, tile, limit) ||
            extensionInRange(e.curve.end(), e.endDir, e.endBisector, tile, limit))
            indices.push_back(i);
    }
}

Channels sampleMsdf(std::span<const Edge> edges, std::span<const size_t> candidates, Point p)
{
    std::array<Selector, 3> selectors;
    for (size_t i : candidates)
    {
        const Edge& edge = edges[i];
        const auto hit   = edge.nearest(p);
        const Point a = p - edge.curve.start(), b = p - edge.curve.end();
        const bool before = a.dot(edge.startBisector) > 0 && a.dot(edge.startDir) < 0;
        const bool after  = b.dot(edge.endBisector) < 0 && b.dot(edge.endDir) > 0;
        for (int c = 0; c < 3; ++c)
        {
            if (!(edge.curve.color & (1u << c)))
                continue;
            selectors[c].consider(hit);
            if (before && std::abs(a.cross(edge.startDir)) < std::abs(hit.distance))
                selectors[c].extend(a.cross(edge.startDir));
            if (after && std::abs(b.cross(edge.endDir)) < std::abs(hit.distance))
                selectors[c].extend(b.cross(edge.endDir));
        }
    }
    return {float(selectors[0].value()), float(selectors[1].value()), float(selectors[2].value())};
}

uint8_t encode(float distance, double range)
{
    return uint8_t(std::lround(std::clamp(0.5 + distance / range, 0., 1.) * 255));
}

void makeInsideRow(
    std::span<const Edge> edges,
    const Frame& frame,
    int y,
    std::vector<std::pair<double, int>>& crossings,
    uint8_t* inside,
    bool halfIntegerSamples)
{
    crossings.clear();
    const double sampleY = frame.sample(0, y).y;
    for (const auto& edge : edges)
        edge.crossings(sampleY, crossings, halfIntegerSamples);
    std::sort(crossings.begin(), crossings.end());
    int winding = 0;
    size_t next = 0;
    for (int x = 0; x < frame.width; ++x)
    {
        const double center = frame.sample(x, y).x;
        while (next < crossings.size() && crossings[next].first <= center)
            winding += crossings[next++].second;
        inside[x] = winding != 0;
    }
}

void flip(Channels& v)
{
    for (float& d : v)
        d = -d;
}

bool setFieldBounds(const Bounds& box, GlyphImage& image)
{
    const int pad = int(std::ceil(image.distanceRangePx / 2)) + 1;
    const double left = std::floor(box.lo.x) - pad, top = std::ceil(box.hi.y) + pad;
    const double width = std::ceil(box.hi.x) + pad - left, height = top - std::floor(box.lo.y) + pad;
    if (width > maxImageSide || height > maxImageSide || width <= 0 || height <= 0 ||
        left < INT32_MIN || left > INT32_MAX || top < INT32_MIN || top > INT32_MAX)
        return false;
    image.leftPx = int32_t(left);
    image.topPx  = int32_t(top);
    image.width  = uint32_t(width);
    image.height = uint32_t(height);
    return true;
}
}  // namespace

RasterResult rasterField(FT_GlyphSlot slot, const RasterRequest& req, bool multi, bool boundsOnly)
{
    GlyphImage image;
    image.encoding        = multi ? RasterEncoding::Msdf : RasterEncoding::Sdf;
    image.distanceRangePx = req.rasterPpem26_6 / (64.f * 4);
    if (!slot->outline.n_points)
        return {GlyphStatus::Ready, std::move(image)};
    // Single-channel SDF layout and rasterization use the same unhinted control box.
    // If distant control points exceed a page, try the normalized ink bounds below.
    if (!multi)
    {
        if (FT_Outline_Check(&slot->outline))
            return {GlyphStatus::RasterError};
        FT_BBox box;
        FT_Outline_Get_CBox(&slot->outline, &box);
        const Bounds controls{{box.xMin / 64., box.yMin / 64.}, {box.xMax / 64., box.yMax / 64.}};
        const bool fits = setFieldBounds(controls, image);
        if (fits && boundsOnly)
            return {GlyphStatus::Ready, std::move(image)};
    }
    Outline outline;
    // SDF permits up to a quarter of one 8-bit distance step during contour union.
    auto status = multi ? prepareBoundary(slot->outline, req, outline)
                        : prepareBoundary(slot->outline, req, outline, image.distanceRangePx / 1020.);
    if (status != GlyphStatus::Ready)
        return {status};
    std::vector<Edge> edges;
    for (auto& contour : outline)
    {
        if (multi)
            colorEdges(contour);
        for (size_t i = 0; i < contour.size(); ++i)
            edges.emplace_back(
                contour[i], contour[(i + contour.size() - 1) % contour.size()], contour[(i + 1) % contour.size()]);
    }
    if (!image.width)
    {
        if (edges.empty())
            return {GlyphStatus::Ready, std::move(image)};
        Bounds box;
        for (const auto& edge : edges)
        {
            box.add(edge.bounds.lo);
            box.add(edge.bounds.hi);
        }
        if (!setFieldBounds(box, image))
            return {GlyphStatus::TooLarge};
    }
    const Frame frame{image.leftPx, image.topPx, int(image.width), int(image.height), image.distanceRangePx};
    const size_t count = size_t(frame.width) * frame.height;
    if (count * (multi ? sizeof(Channels) + 5 : 1) + edges.size() * sizeof(Edge) > maxWorkBytes)
        return {GlyphStatus::TooLarge};
    if (boundsOnly)
        return {GlyphStatus::Ready, std::move(image)};
    image.rowBytes = frame.width * (multi ? 3 : 1);
    image.pixels.resize(size_t(image.rowBytes) * frame.height);
    // Nonempty source contours can cancel completely. Keep the measured rectangle transparent.
    if (edges.empty())
        return {GlyphStatus::Ready, std::move(image)};
    std::vector<Channels> field(multi ? count : 0);
    std::vector<int8_t> signMatches(multi ? count : 0);
    std::vector<uint8_t> inside(tileSize * frame.width);
    std::vector<std::pair<double, int>> crossings;
    std::vector<size_t> candidates;
    std::vector<SdfCandidate> sdfCandidates;
    // SDF encoding saturates at half the range. Keep a rounding margin for
    // edge bounds and squared-distance comparisons.
    const double radius = frame.range * 0.5;
    const double cap2   = radius * radius;
    const double scale  = std::max(std::abs(double(frame.left)), std::abs(double(frame.top))) + maxImageSide;
    const double margin = 1e-6 + 64 * std::numeric_limits<double>::epsilon() * scale;
    const double slack2 = margin * (2 * radius + margin);
    bool signChanged = false;
    for (int y0 = 0; y0 < frame.height; y0 += tileSize)
    {
        const int y1 = std::min(y0 + tileSize, frame.height);
        for (int y = y0; y < y1; ++y)
            makeInsideRow(edges, frame, y, crossings, inside.data() + (y - y0) * frame.width, !multi);
        for (int x0 = 0; x0 < frame.width; x0 += tileSize)
        {
            if (stopped(req))
                return {GlyphStatus::Cancelled};
            const int x1 = std::min(x0 + tileSize, frame.width);
            Bounds tile;
            tile.add(frame.sample(x0, y0));
            tile.add(frame.sample(x1 - 1, y1 - 1));
            if (!multi)
            {
                selectSdfTile(sdfCandidates, edges, tile, cap2 + slack2);
                for (int y = y0; y < y1; ++y)
                    for (int x = x0; x < x1; ++x)
                    {
                        const bool filled = inside[(y - y0) * frame.width + x] != 0;
                        const float d     = sampleSdf(edges, sdfCandidates, frame.sample(x, y), cap2, slack2);
                        image.pixels[size_t(y) * frame.width + x] = encode(filled ? d : -d, frame.range);
                    }
                continue;
            }
            selectMsdfTile(candidates, edges, tile);
            for (int y = y0; y < y1; ++y)
                for (int k = 0; k < x1 - x0; ++k)
                {
                    const int x       = (y % 2) ? x1 - 1 - k : x0 + k;
                    const auto index  = size_t(y) * frame.width + x;
                    const bool filled = inside[(y - y0) * frame.width + x] != 0;
                    auto values       = sampleMsdf(edges, candidates, frame.sample(x, y));
                    const float center = median(values);
                    if (center != 0)
                    {
                        const bool agrees  = (center > 0) == filled;
                        signMatches[index] = agrees ? 1 : -1;
                        if (!agrees)
                        {
                            flip(values);
                            signChanged = true;
                        }
                    }
                    field[index] = values;
                }
        }
    }
    if (multi)
    {
        for (size_t i = 0; i < count; ++i)
        {
            if (signMatches[i])
                continue;
            const size_t x = i % frame.width;
            int votes      = 0;
            if (x)
                votes += signMatches[i - 1];
            if (x + 1 < image.width)
                votes += signMatches[i + 1];
            if (i >= image.width)
                votes += signMatches[i - image.width];
            if (i + image.width < count)
                votes += signMatches[i + image.width];
            if (votes < 0)
            {
                flip(field[i]);
                signChanged = true;
            }
        }
        status = correctMsdf(field, frame, edges, req, signChanged);
        if (status != GlyphStatus::Ready)
            return {status};
        for (size_t i = 0; i < count; ++i)
            for (int c = 0; c < 3; ++c)
                image.pixels[3 * i + c] = encode(field[i][c], frame.range);
    }
    return {GlyphStatus::Ready, std::move(image)};
}
}  // namespace cc::font::detail
