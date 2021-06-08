#include <bits/stdc++.h>
using namespace std;

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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    using point = point2D<int64_t>;

    int n, p;
    cin >> n >> p;

    if (n < 3) return cout << "possible", 0;

    vector<point> a(n);
    for (auto& x : a) cin >> x;

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> rand_range(0, n - 1); // inclusive

    for (int _ = 100, s, t; _--;) {
        s = rand_range(rng);
        for (;;) {
            t = rand_range(rng);
            if (s != t) break;
        }

        int cnt = 0;
        for (const auto& p : a)
            if (p.cross(a[s], a[t]) == 0)
                ++cnt;

        if (n * p <= 100 * cnt)
            return cout << "possible", 0;
    }
    cout << "impossible";
}