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
            return cross(s, e) == 0 && (s - *this).dot(e - *this) <= 1e-8;
    }
    int side_of(const P& s, const P& e) const {
        if constexpr (is_integral_v<T>) {
            auto c = s.cross(e, *this);
            return (c > 0) - (c < 0);
        } else {
            auto a = (e - s).cross(*this - s);
            double l = (e - s).dist() * 1e-8;
            return (a > l) - (a < -l);
        }
    }

    double angle() const { return atan2(y, x); }
    P rotate(double radian) const {
        return P(x * cos(radian) - y * sin(radian), x * sin(radian) + y * cos(radian));
    }
};

template <typename T>
double hull_diameter(const vector<point2D<T>>& hull) {
    T diameter = 0;
    int n = hull.size();
    for (int i = 0, j = n > 1; i < j; ++i) {
        for (;; j = j == n - 1 ? 0 : j + 1) {
            chmax(diameter, (hull[i] - hull[j]).dist2());
            if ((hull[(j + 1) % n] - hull[j]).cross(hull[i + 1] - hull[i]) >= 0)
                break;
        }
    }
    return sqrt(diameter);
}

template <class P = point2D<double>>
P segment_inter(const pair<P, P>& l1, const pair<P, P>& l2) {
    auto& [a, b] = l1;
    auto& [c, d] = l2;
    auto oa = c.cross(d, a), ob = c.cross(d, b);
    return (a * c.cross(d, b) - b * c.cross(d, a)) / (ob - oa);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    using point = point2D<double>;

    int n;
    cin >> n;

    vector<point> a(n);
    for (auto& x : a) cin >> x;

    // precomputed values
    vector<point> perp_units(n);
    for (int i = 0; i < n - 1; ++i)
        perp_units[i] = (a[i + 1] - a[i]).perp_ccw().unit();
    perp_units[n - 1] = (a[0] - a[n - 1]).perp_ccw().unit();

    vector<pair<point, point>> edges;
    vector<point> mini_hull;
    edges.reserve(n), mini_hull.reserve(n);

    auto ok = [&](double R) -> bool {
        edges.clear();
        for (int i = 0; i < n; ++i) {
            pair cur = {a[i] + perp_units[i] * R, a[i == n - 1 ? 0 : i + 1] + perp_units[i] * R};
            // prev edge is outside the polygon
            while (!edges.empty() && edges.back().first.side_of(cur.first, cur.second) == -1)
                edges.pop_back();
            // prev edge is intersected
            if (!edges.empty()) {
                point inter = segment_inter(edges.back(), cur);
                cur.first = edges.back().second = inter;
            }
            edges.emplace_back(cur);
        }

        while (edges.size() > 1 && edges.back().first.side_of(edges.front().first, edges.front().second) == -1)
            edges.pop_back();

        auto st = edges.begin();
        while (edges.end() - st > 1 && st->second.side_of(edges.back().first, edges.back().second) == -1)
            ++st;
        edges.erase(edges.begin(), st);

        if (edges.size() > 1) {
            point inter = segment_inter(edges.back(), edges.front());
            edges.front().first = edges.back().second = inter;
        }

        mini_hull.clear();
        for (const auto& [p, _] : edges) {
            if (!mini_hull.empty() && (p - mini_hull.back()).dist2() < 1e-8) continue;
            mini_hull.emplace_back(p);
        }
        if (mini_hull.size() > 1 && (mini_hull.front() - mini_hull.back()).dist2() < 1e-8)
            mini_hull.pop_back();
        return hull_diameter(mini_hull) >= 2 * R;
    };

    double lo = 0, hi = hull_diameter(a) / 4;
    while (hi - lo > 1e-4) {
        double mid = (lo + hi) / 2;
        (ok(mid) ? lo : hi) = mid;
    }

    cout << fixed << setprecision(3)
         << lo;
}