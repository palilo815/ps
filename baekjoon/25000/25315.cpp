#include <bits/stdc++.h>
using namespace std;

namespace geo {
/* basics */
#define EPS 1e-8
template <typename T, enable_if_t<is_integral<T>::value, bool> = true>
int sign(T x) { return (x > 0) - (x < 0); }
template <typename T, enable_if_t<is_floating_point<T>::value, bool> = true>
int sign(T x) { return (x > EPS) - (x < -EPS); }

/* point2D */
template <typename T>
struct point2D {
    T x, y;
    point2D() = default;
    point2D(T _x, T _y) : x(_x), y(_y) {}
    template <typename U>
    explicit point2D(const point2D<U>& p) : x(p.x), y(p.y) {}

    using P = point2D;

    bool operator<(const P& p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(const P& p) const { return tie(x, y) == tie(p.x, p.y); }
    bool operator!=(const P& p) const { return tie(x, y) != tie(p.x, p.y); }

    friend P operator+(const P& a, const P& b) { return P(a.x + b.x, a.y + b.y); }
    friend P operator-(const P& a, const P& b) { return P(a.x - b.x, a.y - b.y); }
    friend P operator*(const P& a, const T& scalar) { return P(a.x * scalar, a.y * scalar); }
    friend P operator*(const T& scalar, const P& a) { return P(scalar * a.x, scalar * a.y); }
    friend P operator/(const P& a, const T& scalar) { return P(a.x / scalar, a.y / scalar); }

    friend ostream& operator<<(ostream& o, const P& p) { return o << '(' << p.x << ", " << p.y << ')'; }
    friend istream& operator>>(istream& i, P& p) { return i >> p.x >> p.y; }

    T dot(const P& p) const { return x * p.x + y * p.y; }
    T cross(const P& p) const { return x * p.y - y * p.x; }
    T cross(const P& a, const P& b) const { return (a - *this).cross(b - *this); }

    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt(dist2()); }

    P perp_cw() const { return P(y, -x); }
    P perp_ccw() const { return P(-y, x); }

    P unit() const { return *this / dist(); }
    P normal() const { return perp_ccw().unit(); }

    P unit_int() const { return x || y ? *this / gcd(x, y) : *this; }
    P normal_int() const { return perp_ccw().unit_int(); }

    bool same_dir(const P& p) const { return cross(p) == 0 && dot(p) > 0; }
    int side_of(const P& s, const P& e) const {
        if constexpr (is_integral_v<T>) {
            return sign(s.cross(e, *this));
        } else {
            auto res = (e - s).cross(*this - s);
            double l = (e - s).dist() * EPS;
            return (res > l) - (res < -l);
        }
    }

    double angle() const { return atan2(y, x); }
    P rotate(double radian) const {
        return P(x * cos(radian) - y * sin(radian), x * sin(radian) + y * cos(radian));
    }
};
}; // namespace geo

namespace geo::point_in {
template <typename T, enable_if_t<is_integral<T>::value, bool> = true>
bool segment(const point2D<T>& p, const pair<point2D<T>, point2D<T>>& obj) {
    return p.cross(obj.first, obj.second) == 0 &&
           (obj.first - p).dot(obj.second - p) <= 0;
}
template <typename T, enable_if_t<is_floating_point<T>::value, bool> = true>
bool segment(const point2D<T>& p, const pair<point2D<T>, point2D<T>>& obj) {
    return fabs(p.cross(obj.first, obj.second)) < EPS &&
           (obj.first - p).dot(obj.second - p) < EPS;
}

template <typename T>
bool hull(const point2D<T>& p, const vector<point2D<T>>& obj, bool boundary) {
    if (obj.size() < 3) return boundary && point_in::segment(p, pair(obj.front(), obj.back()));

    int lo = 1, hi = obj.size() - 1;
    if (p.side_of(obj[0], obj[lo]) <= -boundary || p.side_of(obj[0], obj[hi]) >= boundary)
        return false;

    while (lo + 1 != hi) {
        int mid = (lo + hi) >> 1;
        (p.side_of(obj[0], obj[mid]) == 1 ? lo : hi) = mid;
    }
    return p.side_of(obj[lo], obj[hi]) > -boundary;
}

template <typename T>
bool polygon(const point2D<T>& p, const vector<point2D<T>>& obj, bool boundary) {
    bool ret = false;
    for (int i = 0; i < int(obj.size()); ++i) {
        const auto s = obj[i], e = obj[i == int(obj.size()) - 1 ? 0 : i + 1];
        if (point_in::segment(p, pair(s, e))) return boundary;
        ret ^= ((p.y < s.y) - (p.y < e.y)) * p.cross(s, e) > 0;
    }
    return ret;
}
}; // namespace geo::point_in

namespace geo::intersected {
template <typename T>
bool segment_segment(const pair<point2D<T>, point2D<T>>& u, const pair<point2D<T>, point2D<T>>& v) {
    if (u.first.side_of(v.first, v.second) * u.second.side_of(v.first, v.second) < 0 &&
        v.first.side_of(u.first, u.second) * v.second.side_of(u.first, u.second) < 0)
        return true;
    return point_in::segment(u.first, v) || point_in::segment(u.second, v) ||
           point_in::segment(v.first, u) || point_in::segment(v.second, u);
}

template <typename T>
bool line_line(const pair<point2D<T>, point2D<T>>& u, const pair<point2D<T>, point2D<T>>& v) {
    return (u.second - u.first).cross(v.second - v.frst) || u.first.side_of(v.first, v.second) == 0;
}
}; // namespace geo::intersected

auto main() -> int {
    cin.tie(nullptr)->sync_with_stdio(false);
    using point = geo::point2D<int64_t>;
    int n;
    cin >> n;
    vector<pair<pair<point, point>, int>> a(n);
    for (auto& [seg, w] : a) {
        cin >> seg.first >> seg.second >> w;
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.second < rhs.second;
    });
    int64_t ans = 0;
    for (int i = 0; i < n; ++i) {
        int64_t cnt = 1;
        for (int j = i + 1; j < n; ++j) {
            cnt += geo::intersected::segment_segment(a[i].first, a[j].first);
        }
        ans += cnt * a[i].second;
    }
    cout << ans;
}
