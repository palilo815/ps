#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

const int M = 1000;
const double pi = 2 * acos(0);

p poly[M];
vector<p> hull;

int ccw(p& a, p& b, p& c) {
    int ret = (b.x - a.x) * (c.y - a.y) -
              (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int dist(p& u, p& v) {
    int dx = u.x - v.x, dy = u.y - v.y;
    return dx * dx + dy * dy;
}
p diff(int i) {
    return {hull[i + 1].x - hull[i].x,
            hull[i + 1].y - hull[i].y};
}
int product(p u, p v) {
    return u.x * v.x + u.y * v.y;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, L; cin >> N >> L;
    loop(i, N) cin >> poly[i].x >> poly[i].y;

    swap(poly[0], *min_element(poly, poly + N));
    sort(poly + 1, poly + N, [&](p & a, p & b) -> bool {
        int ret = ccw(poly[0], a, b);
        return ret ? ret == 1 : dist(poly[0], a) < dist(poly[0], b);
    });

    loop(i, N) {
        while (hull.size() > 1 && ccw(hull[hull.size() - 2], hull[hull.size() - 1], poly[i]) <= 0)
            hull.pop_back();
        hull.emplace_back(poly[i]);
    }

    int sz = hull.size();
    hull.emplace_back(poly[0]);
    hull.emplace_back(poly[1]);

    double ans = 0;
    loop(i, sz) ans += sqrt(dist(hull[i], hull[i + 1]));
    loop(i, sz) {
        double theta = acos(1.0 * product(diff(i), diff(i + 1))
                            / sqrt(dist(hull[i], hull[i + 1])) / sqrt(dist(hull[i + 1], hull[i + 2])));
        ans += theta * L;
    }
    cout << (int)(ans + 0.5);
    return 0;
}