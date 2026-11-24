#include "RasterGeometry.h"
#include "clipper2/clipper.h"
#include FT_OUTLINE_H
#include <map>

namespace cc::font::detail
{
namespace
{
using namespace Clipper2Lib;
constexpr double grid     = 65536.;
constexpr double flatness = 1. / 1024.;  // Maximum chord deviation in generated pixels.

Point fromFT(const FT_Vector* v)
{
    return {v->x / 64., v->y / 64.};
}
Point fromGrid(Point64 v)
{
    return {v.x / grid, v.y / grid};
}
Point64 onGrid(Point v)
{
    return Point64(v.x * grid, v.y * grid);
}

struct OutlineReader
{
    std::vector<Curve> curves;
    std::vector<size_t> starts;
    Point pen;

    int append(Curve c)
    {
        if (curves.size() == curves.capacity())
            return 1;
        curves.push_back(c);
        pen = c.end();
        return 0;
    }
    static int move(const FT_Vector* p, void* data)
    {
        auto& r = *static_cast<OutlineReader*>(data);
        if (r.starts.size() == r.starts.capacity())
            return 1;
        r.starts.push_back(r.curves.size());
        r.pen = fromFT(p);
        return 0;
    }
    static int line(const FT_Vector* p, void* data)
    {
        auto& r = *static_cast<OutlineReader*>(data);
        return r.append({{r.pen, fromFT(p)}, 1});
    }
    static int conic(const FT_Vector* a, const FT_Vector* p, void* data)
    {
        auto& r = *static_cast<OutlineReader*>(data);
        return r.append({{r.pen, fromFT(a), fromFT(p)}, 2});
    }
    static int cubic(const FT_Vector* a, const FT_Vector* b, const FT_Vector* p, void* data)
    {
        auto& r = *static_cast<OutlineReader*>(data);
        return r.append({{r.pen, fromFT(a), fromFT(b), fromFT(p)}, 3});
    }
};

struct Chord
{
    Point64 a, b;
    size_t source;
    double from, to;
};

struct Arc
{
    Point64 a, b;
    size_t source;
    double from, to;
};
constexpr size_t straight = size_t(-1);

bool flat(const Curve& curve)
{
    const Point span     = curve.end() - curve.start();
    const double length2 = span.length2();
    if (length2 <= flatness * flatness &&
        std::all_of(curve.p.begin() + 1, curve.p.begin() + curve.degree, [&](Point p) {
            return (p - curve.start()).length2() <= flatness * flatness;
        }))
        return true;
    double previous = 0;
    for (int i = 1; i < curve.degree; ++i)
    {
        const Point offset = curve.p[i] - curve.start();
        const double along = offset.dot(span);
        if (along < previous || along > length2)
            return false;
        previous = along;
        if (length2 == 0 ? offset.length2() > flatness * flatness
                         : std::abs(offset.cross(span)) > flatness * std::sqrt(length2))
            return false;
    }
    return true;
}

struct BoundaryBuilder
{
    const std::vector<Curve>& curves;
    std::vector<Chord> chords;
    std::map<std::pair<int64_t, int64_t>, std::vector<size_t>> incident;

    bool flatten(const Curve& curve, size_t index, double from, double to, int depth, Path64& path)
    {
        if (!flat(curve))
        {
            if (depth == 30)
                return false;
            Curve a, b;
            curve.split(0.5, a, b);
            const double middle = (from + to) * 0.5;
            return flatten(a, index, from, middle, depth + 1, path) && flatten(b, index, middle, to, depth + 1, path);
        }
        const Point64 a = onGrid(curve.start()), b = onGrid(curve.end());
        if (a == b)
            return true;
        if (chords.size() >= maxBoundaryChords)
            return false;
        path.push_back(a);
        incident[{a.x, a.y}].push_back(chords.size());
        incident[{b.x, b.y}].push_back(chords.size());
        chords.push_back({a, b, index, from, to});
        return true;
    }

    // Clipper rounds new intersection vertices to the integer grid. Recover
    // their original curve parameters, retaining exact Beziers between cuts.
    bool parameter(const Chord& chord, Point64 point, double& t) const
    {
        if (point == chord.a)
        {
            t = chord.from;
            return true;
        }
        if (point == chord.b)
        {
            t = chord.to;
            return true;
        }
        const Point a = fromGrid(chord.a), d = fromGrid(chord.b) - a;
        const Point delta       = fromGrid(point) - a;
        const double projection = delta.dot(d);
        const double len2       = d.length2();
        if (projection < 0 || projection > len2 || std::abs(delta.cross(d)) > 2. / grid * std::sqrt(len2))
            return false;
        double lo = chord.from, hi = chord.to;
        const Curve& curve = curves[chord.source];
        for (int k = 0; k < 36; ++k)
        {
            const double mid = (lo + hi) * 0.5;
            if ((curve.at(mid) - a).dot(d) < projection)
                lo = mid;
            else
                hi = mid;
        }
        t = (lo + hi) * 0.5;
        return true;
    }

    Arc recover(Point64 a, Point64 b) const
    {
        Arc result{a, b, straight, 0, 1};
        auto match = [&](size_t i) {
            const Chord& chord = chords[i];
            if (!parameter(chord, a, result.from) || !parameter(chord, b, result.to))
                return false;
            result.source = chord.source;
            return true;
        };
        for (auto end : {a, b})
        {
            const auto it = incident.find({end.x, end.y});
            if (it != incident.end())
                for (size_t i : it->second)
                    if (match(i))
                        return result;
        }
        // Two new intersections can lie on the same original chord.
        if (!incident.contains({a.x, a.y}) && !incident.contains({b.x, b.y}))
            for (size_t i = 0; i < chords.size(); ++i)
                if (match(i))
                    return result;
        // A union may also replace multiple collinear chords with one line.
        return result;
    }

    Contour restore(const Path64& path) const
    {
        std::vector<Arc> arcs;
        arcs.reserve(path.size());
        for (size_t i = 0; i < path.size(); ++i)
            arcs.push_back(recover(path[i], path[(i + 1) % path.size()]));
        auto joins = [](const Arc& a, const Arc& b) {
            return a.source != straight && a.source == b.source && a.to == b.from && (a.from < a.to) == (b.from < b.to);
        };
        if (joins(arcs.back(), arcs.front()))
        {
            auto begin = arcs.begin() + 1;
            while (begin != arcs.end() && joins(begin[-1], *begin))
                ++begin;
            std::rotate(arcs.begin(), begin, arcs.end());
        }
        Contour contour;
        for (size_t i = 0; i < arcs.size();)
        {
            size_t j = i + 1;
            while (j < arcs.size() && joins(arcs[j - 1], arcs[j]))
                ++j;
            const Arc &first = arcs[i], &last = arcs[j - 1];
            Curve c;
            if (first.source != straight)
                c = curves[first.source].section(first.from, last.to);
            c.p[0]        = fromGrid(first.a);
            c.p[c.degree] = fromGrid(last.b);
            contour.push_back(c);
            i = j;
        }
        return contour;
    }
};
}  // namespace

GlyphStatus prepareBoundary(FT_Outline& outline, const RasterRequest& req, Outline& result)
{
    if (FT_Outline_Check(&outline))
        return GlyphStatus::RasterError;
    OutlineReader input;
    input.curves.reserve(size_t(outline.n_points) + 2 * size_t(outline.n_contours));
    input.starts.reserve(size_t(outline.n_contours) + 1);
    FT_Outline_Funcs functions{
        OutlineReader::move, OutlineReader::line, OutlineReader::conic, OutlineReader::cubic, 0, 0};
    if (FT_Outline_Decompose(&outline, &functions, &input))
        return GlyphStatus::RasterError;
    input.starts.push_back(input.curves.size());
    BoundaryBuilder builder{input.curves, {}, {}};
    Clipper2Lib::Paths64 paths;
    for (size_t c = 1; c < input.starts.size(); ++c)
    {
        Clipper2Lib::Path64 path;
        for (size_t i = input.starts[c - 1]; i < input.starts[c]; ++i)
        {
            if (stopped(req))
                return GlyphStatus::Cancelled;
            if (!builder.flatten(input.curves[i], i, 0, 1, 0, path))
                return GlyphStatus::TooLarge;
        }
        if (path.size() >= 3)
            paths.emplace_back(std::move(path));
    }
    if (paths.empty())
        return GlyphStatus::Ready;
    Clipper2Lib::Clipper64 clip;
    clip.ReverseSolution   = true;  // Y up, ink on the right, including holes.
    clip.PreserveCollinear = true;
    clip.AddSubject(paths);
    Clipper2Lib::Paths64 boundary;
    const auto rule =
        (outline.flags & FT_OUTLINE_EVEN_ODD_FILL) ? Clipper2Lib::FillRule::EvenOdd : Clipper2Lib::FillRule::NonZero;
    if (!clip.Execute(Clipper2Lib::ClipType::Union, rule, boundary))
        return GlyphStatus::RasterError;
    size_t vertices = 0;
    for (const auto& path : boundary)
    {
        if (stopped(req))
            return GlyphStatus::Cancelled;
        vertices += path.size();
        if (vertices > maxBoundaryChords)
            return GlyphStatus::TooLarge;
        if (path.size() >= 3)
            result.push_back(builder.restore(path));
    }
    return GlyphStatus::Ready;
}
}  // namespace cc::font::detail
