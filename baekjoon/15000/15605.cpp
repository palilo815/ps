#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

template <typename T>
struct point2D {
    T x, y;
    point2D() : x(0), y(0) {}
    point2D(T _x, T _y) : x(_x), y(_y) {}
    template <typename U>
    explicit point2D(const point2D<U>& p) : x(p.x), y(p.y) {}

    using P = point2D;

    bool operator<(const P& p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(const P& p) const { return tie(x, y) == tie(p.x, p.y); }
    bool operator!=(const P& p) const { return tie(x, y) != tie(p.x, p.y); }

    friend P operator+(const P& a, const P& b) { return P(a.x + b.x, a.y + b.y); }
    friend P operator-(const P& a, const P& b) { return P(a.x - b.x, a.y - b.y); }
    friend P operator*(const P& a, const T& scala) { return P(a.x * scala, a.y * scala); }
    friend P operator*(const T& scala, const P& a) { return P(scala * a.x, scala * a.y); }
    friend P operator/(const P& a, const T& scala) { return P(a.x / scala, a.y / scala); }

    friend ostream& operator<<(ostream& o, const P& p) { return o << '(' << p.x << ", " << p.y << ')'; }
    friend istream& operator>>(istream& i, P& p) { return i >> p.x >> p.y; }

    T dot(const P& p) const { return x * p.x + y * p.y; }
    T cross(const P& p) const { return x * p.y - y * p.x; }
    T cross(const P& a, const P& b) const { return (a - *this).cross(b - *this); }

    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt(dist2()); }

    P conj() const { return P(x, -y); }
    P perp_cw() const { return P(y, -x); }
    P perp_ccw() const { return P(-y, x); }

    P unit() const { return *this / dist(); }
    P normal() const { return perp_ccw().unit(); }

    P unit_int() const { return x || y ? *this / gcd(x, y) : *this; }
    P normal_int() const { return perp_ccw().unit_int(); }

    bool same_dir(const P& p) const { return cross(p) == 0 && dot(p) > 0; }
    bool on_segment(const P& s, const P& e) const {
        if constexpr (is_integral_v<T>)
            return cross(s, e) == 0 && (s - *this).dot(e - *this) <= 0;
        else
            return cross(s, e) == 0 && (s - *this).dot(e - *this) <= 1e-9;
    }
    int side_of(const P& s, const P& e) const {
        if constexpr (is_integral_v<T>) {
            auto c = s.cross(e, *this);
            return (c > 0) - (c < 0);
        } else {
            auto a = (e - s).cross(*this - s);
            double l = (e - s).dist() * 1e-9;
            return (a > l) - (a < -l);
        }
    }

    double angle() const { return atan2(y, x); }
    P rotate(double radian) const {
        return P(x * cos(radian) - y * sin(radian), x * sin(radian) + y * cos(radian));
    }
};

template <typename T>
bool in_hull(const vector<point2D<T>>& hull, point2D<T> p, bool strict) {
    int a = 1, b = hull.size() - 1, r = !strict;
    if (hull.size() < 3) return r && p.on_segment(hull[0], hull.back());
    if (hull[b].side_of(hull[0], hull[a]) > 0) swap(a, b);
    if (p.side_of(hull[0], hull[a]) >= r || p.side_of(hull[0], hull[b]) <= -r) return false;

    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (p.side_of(hull[0], hull[c]) > 0 ? b : a) = c;
    }

    auto c = hull[a].cross(hull[b], p);
    return ((c > 0) - (c < 0)) < r;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    using point = point2D<double>;

    constexpr double mn = 0, mx = 1e7;

    int n;
    cin >> n;

    vector<point> a(n);
    for (auto& x : a) cin >> x;

    double ans = -1;
    int corners = -1;

    vector<point> hull;

    for (int k = 3; k <= 8; ++k) {
        hull.resize(k);
        double lo = mn, hi = mx;
        while (fabs(hi - lo) > 1e-7) {
            double mid = (lo + hi) / 2;

            hull[0].x = mid;
            for (int i = 1; i < k; ++i)
                hull[i] = hull[i - 1].rotate(2 * M_PI / k);
            any_of(a.begin(), a.end(), [&](auto& pt) { return in_hull(hull, pt, true); }) ? hi = mid : lo = mid;
        }
        double in = lo * lo;

        lo = mn, hi = mx;
        while (fabs(hi - lo) > 1e-6) {
            double mid = (lo + hi) / 2;

            hull[0].x = mid;
            for (int i = 1; i < k; ++i)
                hull[i] = hull[i - 1].rotate(2 * M_PI / k);
            all_of(a.begin(), a.end(), [&](auto& pt) { return in_hull(hull, pt, false); }) ? hi = mid : lo = mid;
        }
        double out = lo * lo;

        if (chmax(ans, in / out))
            corners = k;
    }

    cout << fixed << setprecision(9);
    cout << corners << ' ' << ans;
}