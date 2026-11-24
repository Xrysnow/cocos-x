#include "RasterGeometry.h"

namespace cc::font::detail
{
namespace
{
// RGB interpolation can switch the channel carrying the median between texels.
// Find those switches (also along bilinear cell diagonals) before quantization.
struct Interpolant
{
    Channels a, linear, quadratic;
    Channels at(double t) const
    {
        Channels v;
        for (int c = 0; c < 3; ++c)
            v[c] = float(a[c] + t * (linear[c] + t * quadratic[c]));
        return v;
    }
};

double referenceDistance(Point p, std::span<const Edge> edges)
{
    double nearest = std::numeric_limits<double>::infinity();
    std::vector<std::pair<double, int>> crossings;
    for (const auto& edge : edges)
    {
        if (edge.bounds.distance2({p, p}) <= nearest * nearest)
            nearest = std::min(nearest, std::abs(edge.nearest(p).distance));
        if (p.y >= edge.bounds.lo.y && p.y <= edge.bounds.hi.y && edge.bounds.lo.x <= p.x)
            edge.crossings(p.y, crossings);
    }
    int winding = 0;
    for (auto [x, d] : crossings)
        if (x <= p.x)
            winding += d;
    return winding ? nearest : -nearest;
}

bool artifact(
    const Interpolant& f,
    const Channels& last,
    Point start,
    Point step,
    std::span<const Edge> edges,
    bool protect,
    bool useReference,
    bool diagonal)
{
    const double ma = median(f.a), mb = median(last);
    if (std::abs(ma) < std::abs(mb) || (f.a[0] == f.a[1] && f.a[1] == f.a[2]))
        return false;
    const double span = std::sqrt(step.length2()) * 10. / 9.;
    auto check        = [&](double t) {
        const Channels rgb   = f.at(t);
        const double m       = median(rgb);
        const bool inversion = (ma > 0 && mb > 0 && m < 0) || (ma < 0 && mb < 0 && m > 0);
        // A true signed distance is 1-Lipschitz. Leave normal contour crossings intact.
        const bool spike = std::abs(m - ma) > span * t + 1e-5 || std::abs(m - mb) > span * (1 - t) + 1e-5;
        if (!inversion && (protect || !spike || (m >= std::min(ma, mb) && m <= std::max(ma, mb))))
            return false;
        if (!useReference)
            return true;
        const double reference = referenceDistance(start + step * t, edges);
        Channels fixed         = rgb;
        const double weight    = diagonal ? (1 - t) * (1 - t) : (1 - t);
        for (int c = 0; c < 3; ++c)
            fixed[c] += float(weight * (ma - f.a[c]));
        return std::abs(m - reference) > 1e-5 + 10. / 9. * std::abs(median(fixed) - reference);
    };
    double roots[2];
    for (int c = 0; c < 3; ++c)
    {
        const int k               = (c + 1) % 3;
        const double polynomial[] = {f.a[c] - f.a[k], f.linear[c] - f.linear[k], f.quadratic[c] - f.quadratic[k]};
        const int n               = unitRoots(polynomial, 2, roots);
        for (int i = 0; i < n; ++i)
            if (check(roots[i]))
                return true;
        if (diagonal && f.quadratic[c] != 0)
        {
            const double t = -f.linear[c] / (2. * f.quadratic[c]);
            if (t > 0 && t < 1 && check(t))
                return true;
        }
    }
    return false;
}
}  // namespace

GlyphStatus correctMsdf(
    std::vector<Channels>& field,
    const Frame& frame,
    std::span<const Edge> edges,
    const RasterRequest& req,
    bool signChanged)
{
    std::vector<uint8_t> marks(field.size());
    for (const auto& edge : edges)
    {
        if (std::abs(edge.startDir.cross(edge.startBisector)) < 1e-5 && edge.startBisector.dot(edge.startDir) > 0)
            continue;
        const auto p = edge.curve.start();
        const int x = int(std::floor(p.x - frame.left - 0.5)), y = int(std::floor(frame.top - p.y - 0.5));
        for (int j = std::max(0, y); j <= std::min(frame.height - 1, y + 1); ++j)
            for (int i = std::max(0, x); i <= std::min(frame.width - 1, x + 1); ++i)
                marks[size_t(j) * frame.width + i] = 1;
    }
    for (int y = 0; y < frame.height; ++y)
    {
        if (stopped(req))
            return GlyphStatus::Cancelled;
        for (int x = 0; x < frame.width; ++x)
        {
            const auto index = size_t(y) * frame.width + x;
            const auto a     = field[index];
            if (a[0] == a[1] && a[1] == a[2])
                continue;
            bool marked = false;
            for (int dy = -1; dy <= 1 && !marked; ++dy)
                for (int dx = -1; dx <= 1 && !marked; ++dx)
                {
                    if ((!dx && !dy) || x + dx < 0 || x + dx >= frame.width || y + dy < 0 || y + dy >= frame.height)
                        continue;
                    const bool diagonal = dx && dy;
                    const size_t row    = size_t(y + dy) * frame.width;
                    const Channels b    = field[row + x + dx];
                    Interpolant f{a, {}, {}};
                    for (int c = 0; c < 3; ++c)
                    {
                        f.linear[c]    = diagonal
                                             ? field[size_t(y) * frame.width + x + dx][c] + field[row + x][c] - 2 * a[c]
                                             : b[c] - a[c];
                        f.quadratic[c] = diagonal ? b[c] - a[c] - f.linear[c] : 0;
                    }
                    marked = artifact(
                        f,
                        b,
                        frame.sample(x, y),
                        {double(dx), double(-dy)},
                        edges,
                        marks[index] == 1 || std::abs(median(a)) < 0.5,
                        !signChanged,
                        diagonal);
                }
            if (marked)
                marks[index] = 2;
        }
    }
    for (size_t i = 0; i < marks.size(); ++i)
        if (marks[i] == 2)
            field[i].fill(median(field[i]));
    return GlyphStatus::Ready;
}
}  // namespace cc::font::detail
