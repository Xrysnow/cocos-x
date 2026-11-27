#pragma once

#include "GlyphRasterizer.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <span>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace cc::font::detail
{
constexpr int maxImageSide         = 2048 - 2;  // One atlas guard texel on either side.
constexpr size_t maxWorkBytes      = 32u << 20;
constexpr size_t maxBoundaryChords = 32768;
inline bool stopped(const RasterRequest& req)
{
    return req.cancelled && req.cancelled->load(std::memory_order_relaxed);
}

struct Point
{
    double x{}, y{};
    Point operator+(Point b) const { return {x + b.x, y + b.y}; }
    Point operator-(Point b) const { return {x - b.x, y - b.y}; }
    Point operator*(double s) const { return {x * s, y * s}; }
    double dot(Point b) const { return x * b.x + y * b.y; }
    double cross(Point b) const { return x * b.y - y * b.x; }
    double length2() const { return dot(*this); }
    Point unit() const;
};

struct Bounds
{
    Point lo{std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()};
    Point hi{-lo.x, -lo.y};
    void add(Point p);
    double distance2(const Bounds& other) const
    {
        const double x = std::max(std::max(0., lo.x - other.hi.x), other.lo.x - hi.x);
        const double y = std::max(std::max(0., lo.y - other.hi.y), other.lo.y - hi.y);
        return x * x + y * y;
    }
};

// Roots in the open unit interval, sorted. Coefficients are in ascending power order.
int unitRoots(const double* coefficients, int degree, double* roots);

struct Curve
{
    std::array<Point, 4> p{};
    int degree{1};
    unsigned color{7};
    Point start() const { return p[0]; }
    Point end() const { return p[degree]; }
    Point at(double t) const;
    Point tangent(bool atEnd) const;
    void split(double t, Curve& first, Curve& last) const;
    Curve section(double from, double to) const;
    Bounds bounds() const;
};
using Contour = std::vector<Curve>;
using Outline = std::vector<Contour>;
struct Edge
{
    Curve curve;
    Bounds bounds;
    std::array<Point, 4> power{};
    std::array<double, 6> stationary{};
    Point startDir, endDir, startBisector, endBisector;
    Edge(const Curve&, const Curve& previous, const Curve& next);
    struct Hit
    {
        double distance, alignment, pseudo;
    };
    Hit nearest(Point q) const;
    double nearestDistance2(Point q) const;
    // With halfIntegerSamples, x positions are accurate only for classification
    // against half-integer sample centers. The crossing direction is unchanged.
    void crossings(double y, std::vector<std::pair<double, int>>& out, bool halfIntegerSamples = false) const;
    int windingAt(Point p) const;

private:
    double nearestParameter(Point q) const;
};

struct Frame
{
    int left, top, width, height;
    double range;
    Point sample(int x, int y) const { return {left + 0.5 + x, top - 0.5 - y}; }
};
using Channels = std::array<float, 3>;
inline float median(Channels v)
{
    return std::max(std::min(v[0], v[1]), std::min(std::max(v[0], v[1]), v[2]));
}

GlyphStatus validateFace(FT_Face face);
GlyphStatus prepareBoundary(FT_Outline&, const RasterRequest&, Outline&);
GlyphStatus prepareBoundary(FT_Outline&, const RasterRequest&, Outline&, double flatness);
void colorEdges(Contour&);
RasterResult rasterBitmap(FT_GlyphSlot, const RasterRequest&);
RasterResult copyBitmap(const FT_Bitmap&, int left, int top);
RasterResult rasterField(FT_GlyphSlot, const RasterRequest&, bool multiChannel, bool boundsOnly = false);
GlyphStatus correctMsdf(
    std::vector<Channels>&, const Frame&, std::span<const Edge>, const RasterRequest&, bool signChanged);
}  // namespace cc::font::detail
