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

template <typename T>
bool segment_inter(const point2D<T>& a, const point2D<T>& b, const point2D<T>& c, const point2D<T>& d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c), od = a.cross(b, d);

    auto sgn = [](auto x) { return (x > 0) - (x < 0); };
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return true;
    return a.on_segment(c, d) || b.on_segment(c, d) || c.on_segment(a, b) || d.on_segment(a, b);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    using point = point2D<int64_t>;

    int T;
    cin >> T;

    array<point, 2> line;
    array<point, 4> rec;

    while (T--) {
        cin >> line[0] >> line[1];
        cin >> rec[0] >> rec[2];

        if (rec[0].x > rec[2].x) swap(rec[0].x, rec[2].x);
        if (rec[0].y > rec[2].y) swap(rec[0].y, rec[2].y);

        if (rec[0].x <= line[0].x && line[0].x <= rec[2].x &&
            rec[0].y <= line[0].y && line[0].y <= rec[2].y &&
            rec[0].x <= line[1].x && line[1].x <= rec[2].x &&
            rec[0].y <= line[1].y && line[1].y <= rec[2].y) {
            cout << "T\n";
            continue;
        }

        rec[1] = rec[3] = rec[0];
        rec[1].x += rec[2].x - rec[0].x;
        rec[3].y += rec[2].y - rec[0].y;

        if (segment_inter(line[0], line[1], rec[0], rec[1]) ||
            segment_inter(line[0], line[1], rec[1], rec[2]) ||
            segment_inter(line[0], line[1], rec[2], rec[3]) ||
            segment_inter(line[0], line[1], rec[3], rec[0]))
            cout << "T\n";
        else
            cout << "F\n";
    }
}