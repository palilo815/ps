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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    using point = point2D<int64_t>;

    int n;
    cin >> n;

    vector<point> a(n);
    for (auto& x : a) cin >> x;

    array<vector<point>, 4> quadrant;
    array<int, 4> axis; // +x, +y, -x, -y

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (auto& v : quadrant) v.clear();
        fill(axis.begin(), axis.end(), 0);

        for (int j = 0; j < n; ++j)
            if (i != j) {
                point p = (a[j] - a[i]).unit_int();
                if (p.x) {
                    if (p.y)
                        quadrant[(p.y < 0) << 1 | (p.x * p.y < 0)].emplace_back(p);
                    else
                        p.x > 0 ? ++axis[0] : ++axis[2];
                } else
                    p.y > 0 ? ++axis[1] : ++axis[3];
            }

        for (auto& v : quadrant)
            sort(v.begin(), v.end(), [&](auto& lhs, auto& rhs) {
                return lhs.cross(rhs) > 0;
            });

        for (int j = 0; j < 4; ++j)
            ans += axis[j] * axis[(j + 1) & 3];

        for (int j = 0; j < 4; ++j) {
            const auto &vl = quadrant[j], vr = quadrant[(j + 1) & 3];
            for (int l = 0, l2, r = 0; l < int(vl.size()); l = l2) {
                for (l2 = l + 1; l2 < int(vl.size()) && vl[l] == vl[l2]; ++l2)
                    ;
                point key = vl[l].perp_ccw();
                while (r < int(vr.size()) && vr[r].cross(key) > 0) ++r;
                while (r < int(vr.size()) && vr[r] == key) ++r, ans += l2 - l;
            }
        }
    }
    cout << ans;
}