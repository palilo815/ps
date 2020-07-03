#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using ll = long long;
using p = pair<int, int>;

const int M = 200000;

int N, sz;
p poly[M];
vector<p> hull;

int ccw(p& a, p& b, p& c) {
    ll ret = 1LL * (b.x - a.x) * (c.y - a.y) -
             1LL * (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
ll dist(p& u, p& v) {
    ll dx = u.x - v.x, dy = u.y - v.y;
    return dx * dx + dy * dy;
}
p diff(int i) {
    return {hull[i + 1].x - hull[i].x,
            hull[i + 1].y - hull[i].y};
}
void input() {
    cin >> N;
    loop(i, N) cin >> poly[i].x >> poly[i].y;
}
void convex_hull() {
    swap(poly[0], *min_element(poly, poly + N));
    sort(poly + 1, poly + N, [&](p & a, p & b) -> bool {
        int ret = ccw(poly[0], a, b);
        return ret ? ret == 1 : dist(poly[0], a) < dist(poly[0], b);
    });

    hull = {poly[0], poly[1]};
    for (int i = 2; i < N; ++i) {
        while (hull.size() > 1 && ccw(hull[hull.size() - 2], hull[hull.size() - 1], poly[i]) <= 0)
            hull.pop_back();
        hull.emplace_back(poly[i]);
    }
}
void solve() {
    ll d_max = 0;
    p ori = {0, 0}, v1, v2;
    int j = 0, u, v, sz = hull.size();
    loop(i, sz) {
        while (j + 1 < sz && ccw(ori, v1 = diff(i), v2 = diff(j)) >= 0) {
            ll d = dist(hull[i], hull[j]);
            if (d > d_max)
                d_max = d, u = i, v = j;
            ++j;
        }
        ll d = dist(hull[i], hull[j]);
        if (d > d_max)
            d_max = d, u = i, v = j;
    }
    cout << hull[u].x << ' ' << hull[u].y << ' '
         << hull[v].x << ' ' << hull[v].y << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        input();
        convex_hull();
        solve();
    }
    return 0;
}