#include <bits/extc++.h>
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

    int hash_val() const { return (x + 10000) << 16 | (y + 10000); }
};

using point = point2D<int>;
array<point, 3000> a;

int solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    sort(a.begin(), a.begin() + n);

    __gnu_pbds::gp_hash_table<int, __gnu_pbds::null_type> hash_set;
    for (int i = 0; i < n; ++i)
        hash_set.insert(a[i].hash_val());

    int ans = 0;
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j) {
            point v = a[j] - a[i];
            int area = v.dist2();
            if (area <= ans) continue;

            point p1 = a[i] + v.perp_cw(), p2 = p1 + v;
            if (hash_set.find(p1.hash_val()) != hash_set.end() &&
                hash_set.find(p2.hash_val()) != hash_set.end())
                ans = area;
        }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) cout << solve() << '\n';
}