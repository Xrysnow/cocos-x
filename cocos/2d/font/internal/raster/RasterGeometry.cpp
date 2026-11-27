#include "RasterGeometry.h"

namespace cc::font::detail
{
Point Point::unit() const
{
    const double len = std::sqrt(length2());
    return len ? *this * (1.0 / len) : Point{};
}

void Bounds::add(Point p)
{
    lo = {std::min(lo.x, p.x), std::min(lo.y, p.y)};
    hi = {std::max(hi.x, p.x), std::max(hi.y, p.y)};
}

static double evaluate(const double* c, int degree, double t)
{
    double value = c[degree];
    while (degree > 0)
        value = value * t + c[--degree];
    return value;
}

static double bracketRoot(const double* c, int degree, const double* derivative, double a, double b, double f0)
{
    double t = (a + b) * 0.5;
    for (int iter = 0; iter < 50; ++iter)
    {
        const double value = evaluate(c, degree, t);
        if (value == 0)
            break;
        if (std::signbit(value) == std::signbit(f0))
            a = t;
        else
            b = t;
        if (b - a < 1e-13)
            break;
        const double slope = evaluate(derivative, degree - 1, t);
        const double next  = slope ? t - value / slope : (a + b) * 0.5;
        if (std::abs(next - t) <= 1e-14)
            break;
        t = (next > a && next < b) ? next : (a + b) * 0.5;
    }
    return t;
}

int unitRoots(const double* c, int degree, double* roots)
{
    while (degree > 0 && c[degree] == 0)
        --degree;
    if (!degree)
        return 0;
    if (degree == 1)
    {
        const double t = -c[0] / c[1];
        if (!(t > 0 && t < 1))
            return 0;
        roots[0] = t;
        return 1;
    }

    // Isolate monotone intervals with the roots of the derivative. A repeated
    // root can sit at an interval endpoint without changing the sign.
    double derivative[5], knots[7]{};
    double norm = std::abs(c[0]);
    for (int i = 1; i <= degree; ++i)
    {
        derivative[i - 1]  = i * c[i];
        norm              += std::abs(c[i]);
    }
    const int last = 1 + unitRoots(derivative, degree - 1, knots + 1);
    knots[last]    = 1;
    int count      = 0;
    double f0      = c[0];
    for (int i = 1; i <= last; ++i)
    {
        double a = knots[i - 1], b = knots[i];
        double f1 = evaluate(c, degree, b);
        if (i != last && std::abs(f1) <= 8 * std::numeric_limits<double>::epsilon() * norm)
            f1 = 0;
        if (f0 && f1 && std::signbit(f0) != std::signbit(f1))
        {
            roots[count++] = bracketRoot(c, degree, derivative, a, b, f0);
        }
        if (f1 == 0 && i < last)
            roots[count++] = b;
        f0 = f1;
    }
    return count;
}

static std::array<Point, 4> coefficients(const Curve& c)
{
    const auto& p = c.p;
    std::array<Point, 4> out{p[0], (p[1] - p[0]) * c.degree};
    if (c.degree >= 2)
        out[2] = (p[2] - p[1] * 2 + p[0]) * (c.degree == 2 ? 1. : 3.);
    if (c.degree == 3)
        out[3] = p[3] - p[2] * 3 + p[1] * 3 - p[0];
    return out;
}

Point Curve::at(double t) const
{
    auto points = p;
    for (int n = degree; n > 0; --n)
        for (int j = 0; j < n; ++j)
            points[j] = points[j] + (points[j + 1] - points[j]) * t;
    return points[0];
}

Point Curve::tangent(bool atEnd) const
{
    for (int i = 1; i <= degree; ++i)
    {
        const Point diff = atEnd ? end() - p[degree - i] : p[i] - start();
        if (diff.length2())
            return diff.unit();
    }
    return {};
}

void Curve::split(double t, Curve& first, Curve& last) const
{
    first = last = *this;
    auto points  = p;
    for (int k = 1; k <= degree; ++k)
    {
        for (int j = 0; j <= degree - k; ++j)
            points[j] = points[j] + (points[j + 1] - points[j]) * t;
        first.p[k]         = points[0];
        last.p[degree - k] = points[degree - k];
    }
}

Curve Curve::section(double from, double to) const
{
    if (from > to)
    {
        Curve reversed = section(to, from);
        std::reverse(reversed.p.begin(), reversed.p.begin() + degree + 1);
        return reversed;
    }
    Curve segment = *this, discarded;
    if (to < 1)
        split(to, segment, discarded);
    if (from > 0)
    {
        Curve suffix;
        segment.split(from / to, discarded, suffix);
        segment = suffix;
    }
    return segment;
}

Bounds Curve::bounds() const
{
    Bounds box;
    box.add(start());
    box.add(end());
    const auto a = coefficients(*this);
    for (int axis = 0; axis < 2; ++axis)
    {
        double derivative[3]{}, extrema[2]{};
        for (int i = 1; i <= degree; ++i)
            derivative[i - 1] = i * (axis ? a[i].y : a[i].x);
        const int count = unitRoots(derivative, degree - 1, extrema);
        for (int i = 0; i < count; ++i)
            box.add(at(extrema[i]));
    }
    return box;
}

Edge::Edge(const Curve& c, const Curve& previous, const Curve& next)
    : curve(c), bounds(c.bounds()), power(coefficients(c)), startDir(c.tangent(false)), endDir(c.tangent(true)),
      startBisector((previous.tangent(true) + startDir).unit()), endBisector((endDir + next.tangent(false)).unit())
{
    for (int i = 0; i <= c.degree; ++i)
        for (int j = 1; j <= c.degree; ++j)
            stationary[i + j - 1] += power[i].dot(power[j]) * j;
}

// The stationary polynomial of a quadratic Bezier has at most three roots.
static int quadraticStationaryRoots(const double* c, double* roots)
{
    if (c[3] > 0)
    {
        const double end   = evaluate(c, 3, 1.);
        const double slack = 64 * std::numeric_limits<double>::epsilon() *
                             (std::abs(c[0]) + std::abs(c[1]) + std::abs(c[2]) + c[3]);
        // A Bernstein polynomial stays in the convex hull of its coefficients.
        const double b1 = c[0] + c[1] / 3, b2 = c[0] + (2 * c[1] + c[2]) / 3;
        if (std::min({c[0], b1, b2, end}) > slack || std::max({c[0], b1, b2, end}) < -slack)
            return 0;
        if (c[0] < -slack && end > slack &&
            std::min({c[1], c[1] + c[2], c[1] + 2 * c[2] + 3 * c[3]}) > slack)
        {
            // Strictly increasing throughout. Use the original bracket and iteration.
            const double derivative[]{c[1], 2 * c[2], 3 * c[3]};
            roots[0] = bracketRoot(c, 3, derivative, 0., 1., c[0]);
            return 1;
        }
    }
    return unitRoots(c, 3, roots);
}

double Edge::nearestParameter(Point q) const
{
    double t       = 0;
    double squared = (q - curve.start()).length2();
    if (curve.degree == 1)
        t = std::clamp((q - curve.start()).dot(power[1]) / power[1].length2(), 0., 1.);
    else
    {
        const double endDistance = (q - curve.end()).length2();
        if (endDistance < squared)
        {
            t       = 1;
            squared = endDistance;
        }
        auto equation = stationary;
        for (int i = 1; i <= curve.degree; ++i)
            equation[i - 1] -= q.dot(power[i]) * i;
        double candidates[5];
        const int count = curve.degree == 2 ? quadraticStationaryRoots(equation.data(), candidates)
                                            : unitRoots(equation.data(), 5, candidates);
        for (int i = 0; i < count; ++i)
        {
            const double d = (q - curve.at(candidates[i])).length2();
            if (d < squared)
            {
                squared = d;
                t       = candidates[i];
            }
        }
    }
    return t;
}

double Edge::nearestDistance2(Point q) const
{
    return (q - curve.at(nearestParameter(q))).length2();
}

Edge::Hit Edge::nearest(Point q) const
{
    double t;
    Point closest, direction = startDir;
    if (curve.degree == 1)
    {
        const double length2 = power[1].length2();
        t = length2 ? std::clamp((q - curve.start()).dot(power[1]) / length2, 0., 1.) : 0.;
        closest = curve.start() + power[1] * t;
    }
    else
    {
        t = nearestParameter(q);
        closest = curve.at(t);
        if (t > 0 && t < 1)
        {
            direction = power[1] + power[2] * (2 * t) + power[3] * (3 * t * t);
            if (!direction.length2())
                direction = curve.at(std::min(1., t + 1e-6)) - closest;
            direction = direction.unit();
        }
    }
    if (t == 1)
        direction = endDir;
    const Point delta       = q - closest;
    const double normal     = delta.cross(direction);
    const double distance   = std::copysign(std::sqrt(delta.length2()), normal);
    const double projection = delta.dot(direction);
    const bool extended     = (t == 0 && projection < 0) || (t == 1 && projection > 0);
    const double alignment  = ((t == 0 || t == 1) && distance) ? std::abs(projection / distance) : 0;
    return {distance, alignment, extended ? normal : distance};
}

enum class CrossingMode { Exact, PixelCenters, QueryX };

template <typename Emit>
static void visitCrossings(const Edge& edge, double y, CrossingMode mode, double queryX, Emit emit)
{
    if (y < edge.bounds.lo.y || y >= edge.bounds.hi.y)
        return;
    const auto& curve = edge.curve;
    const auto& power = edge.power;
    if (curve.degree == 1)
    {
        emit(curve.start().x + (y - curve.start().y) * power[1].x / power[1].y, power[1].y > 0 ? 1 : -1);
        return;
    }
    double deriv[3]{power[1].y, 2 * power[2].y, 3 * power[3].y};
    double knots[4]{};
    const int last = 1 + unitRoots(deriv, curve.degree - 1, knots + 1);
    knots[last]    = 1;
    double maxDx = 0, slack = 0;
    if (mode != CrossingMode::Exact)
    {
        double scale = std::max(1., std::abs(curve.start().x));
        for (int i = 1; i <= curve.degree; ++i)
        {
            scale = std::max(scale, std::abs(curve.p[i].x));
            maxDx = std::max(maxDx, std::abs(curve.p[i].x - curve.p[i - 1].x));
        }
        maxDx *= curve.degree;
        slack = 64 * std::numeric_limits<double>::epsilon() * scale;
    }
    for (int i = 0; i < last; ++i)
    {
        double a = knots[i], b = knots[i + 1];
        const double ya = curve.at(a).y, yb = curve.at(b).y;
        if (y < std::min(ya, yb) || y >= std::max(ya, yb))
            continue;
        Point middle;
        for (int k = 0; k < 42; ++k)
        {
            const double mid = (a + b) * 0.5;
            middle = curve.at(mid);
            if (mode != CrossingMode::Exact && (k == 8 || k == 16 || k == 24))
            {
                const double cutoff = mode == CrossingMode::QueryX ? queryX : std::round(middle.x - 0.5) + 0.5;
                // The derivative control points bound horizontal travel in this bracket.
                if (std::abs(middle.x - cutoff) > maxDx * (b - a) * 0.5 + slack)
                    break;
            }
            if ((middle.y < y) == (ya < yb))
                a = mid;
            else
                b = mid;
            if (k == 41)
                middle = curve.at((a + b) * 0.5);
        }
        emit(middle.x, ya < yb ? 1 : -1);
    }
}

void Edge::crossings(double y, std::vector<std::pair<double, int>>& out, bool halfIntegerSamples) const
{
    visitCrossings(*this, y, halfIntegerSamples ? CrossingMode::PixelCenters : CrossingMode::Exact, 0.,
                   [&](double x, int direction) { out.emplace_back(x, direction); });
}

int Edge::windingAt(Point p) const
{
    if (p.y < bounds.lo.y || p.y >= bounds.hi.y || bounds.lo.x > p.x)
        return 0;
    if (bounds.hi.x < p.x)
    {
        double maxX = curve.start().x;
        for (int i = 1; i <= curve.degree; ++i)
            maxX = std::max(maxX, curve.p[i].x);
        const double slack = 64 * std::numeric_limits<double>::epsilon() * std::max(1., std::abs(p.x));
        // With the entire hull to the left, the internal monotone endpoints cancel.
        if (maxX + slack < p.x)
        {
            const double endY = curve.degree == 1 ? curve.end().y : curve.at(1).y;
            return int(endY > p.y) - int(curve.start().y > p.y);
        }
    }
    int winding = 0;
    visitCrossings(*this, p.y, CrossingMode::QueryX, p.x, [&](double x, int direction) {
        if (x <= p.x)
            winding += direction;
    });
    return winding;
}
}  // namespace cc::font::detail
