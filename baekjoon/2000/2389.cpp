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

template <class P = point2D<double>>
double circle_radius(const P& A, const P& B, const P& C) {
    return (B - A).dist() * (C - B).dist() * (A - C).dist() / Abs((B - A).cross(C - A)) / 2;
}
template <class P = point2D<double>>
point2D<double> circle_centre(const P& A, const P& B, const P& C) {
    auto b = C - A, c = B - A;
    return A + (b * c.dist2() - c * b.dist2()).perp_ccw() / b.cross(c) / 2;
}

template <class P = point2D<double>>
pair<P, double> mec(vector<P> ps) {
    shuffle(ps.begin(), ps.end(), mt19937(time(0)));
    P o = ps[0];
    double r = 0, EPS = 1 + 1e-8;

    for (int i = 0; i < int(ps.size()); ++i) {
        if ((o - ps[i]).dist() > r * EPS) {
            o = ps[i], r = 0;
            for (int j = 0; j < i; ++j)
                if ((o - ps[j]).dist() > r * EPS) {
                    o = (ps[i] + ps[j]) / 2;
                    r = (o - ps[i]).dist();
                    for (int k = 0; k < j; ++k)
                        if ((o - ps[k]).dist() > r * EPS) {
                            o = circle_centre(ps[i], ps[j], ps[k]);
                            r = (o - ps[i]).dist();
                        }
                }
        }
    }
    return {o, r};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    using point = point2D<double>;

    int n;
    cin >> n;

    vector<point> a(n);
    for (auto& x : a) cin >> x;

    auto ans = mec(move(a));

    cout << fixed << setprecision(9)
         << ans.first.x << ' ' << ans.first.y << ' ' << ans.second;
}