#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

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

namespace geo {
template <typename T>
vector<point2D<T>> convex_hull(vector<point2D<T>>& pts) {
    if (pts.size() <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<point2D<T>> hull(pts.size() + 1);
    size_t s = 0, t = 0;
    for (const auto& p : pts) {
        while (t >= s + 2 && hull[t - 2].cross(hull[t - 1], p) <= 0) --t;
        hull[t++] = p;
    }
    s = --t;
    reverse(pts.begin(), pts.end());
    for (const auto& p : pts) {
        while (t >= s + 2 && hull[t - 2].cross(hull[t - 1], p) <= 0) t--;
        hull[t++] = p;
    }
    return {hull.begin(), hull.begin() + t - (t == 2 && hull[0] == hull[1])};
}
}; // namespace geo

namespace geo::distance2 {
template <typename T>
T hull_diameter(const vector<point2D<T>>& hull) {
    if (hull.size() < 2) return 0;
    T diameter = 0;
    const size_t n = hull.size();
    for (size_t i = 0, j = 1, j2; i < j; ++i) {
        for (;; j = j2) {
            j2 = j == n - 1 ? 0 : j + 1;
            chmax(diameter, (hull[i] - hull[j]).dist2());
            if ((hull[j2] - hull[j]).cross(hull[i + 1] - hull[i]) >= 0) {
                break;
            }
        }
    }
    return diameter;
}
}; // namespace geo::distance2

struct star_t {
    int x, y, dx, dy;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, t;
    cin >> n >> t;
    vector<star_t> a(n);
    for (auto& [x, y, dx, dy] : a) {
        cin >> x >> y >> dx >> dy;
    }
    using point = geo::point2D<int64_t>;
    vector<point> star(n);
    auto f = [&](int dt) -> int64_t {
        transform(a.begin(), a.end(), star.begin(), [&](const auto& star) {
            return point(star.x + star.dx * dt, star.y + star.dy * dt);
        });
        return geo::distance2::hull_diameter(geo::convex_hull(star));
    };
    int lo = 0, hi = t;
    while (lo != hi) {
        const auto ml = lo + (hi - lo) / 3;
        const auto mr = hi - (hi - lo) / 3;
        f(ml) <= f(mr) ? hi = mr - 1 : lo = ml + 1;
    }
    cout << lo << '\n';
    cout << f(lo);
}