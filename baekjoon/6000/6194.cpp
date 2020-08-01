#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using p = pair<int, int>;
using ll = long long;

const int mxN = 5e3;

p poly[mxN];

int ccw(p& a, p& b, p& c) {
    int ret = (b.x - a.x) * (c.y - a.y) -
              (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
ll dist(p& u, p& v) {
    ll dx = u.x - v.x, dy = u.y - v.y;
    return dx * dx + dy * dy;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> poly[i].x >> poly[i].y;

    swap(poly[0], *min_element(poly, poly + N));
    sort(poly + 1, poly + N, [&](p & a, p & b) {
        int ret = ccw(poly[0], a, b);
        return ret ? ret == 1 : dist(poly[0], a) < dist(poly[0], b);
    });

    vector<p> hull;
    loop(i, N) {
        while (hull.size() > 1 && ccw(hull[hull.size() - 2], hull[hull.size() - 1], poly[i]) <= 0)
            hull.pop_back();
        hull.emplace_back(poly[i]);
    }

    N = hull.size();
    hull.emplace_back(hull[0]);

    double ans = 0;
    loop(i, N) ans += sqrt(dist(hull[i], hull[i + 1]));
    cout << fixed << setprecision(2) << ans;
    return 0;
}