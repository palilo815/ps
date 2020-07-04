#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using ll = long long;
using p = pair<int, int>;

const int M = 4096;

int N, sz;
p poly[M], hull[M + 1];

int ccw(p& a, p& b, p& c) {
    ll ret = (ll)(b.x - a.x) * (c.y - a.y) -
             (ll)(b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
ll area(p& a, p& b, p& c) {
    return (ll)(b.x - a.x) * (c.y - a.y) - (ll)(b.y - a.y) * (c.x - a.x);
}
ll dist(p& v) {
    ll dx = poly[0].x - v.x, dy = poly[0].y - v.y;
    return dx * dx + dy * dy;
}
void input() {
    cin >> N;
    loop(i, N) cin >> poly[i].x >> poly[i].y;
}
void convex_hull() {
    swap(poly[0], *min_element(poly, poly + N));
    sort(poly + 1, poly + N, [&](p & a, p & b) -> bool {
        int ret = ccw(poly[0], a, b);
        return ret ? ret == 1 : dist(a) < dist(b);
    });

    sz = 0;
    loop(i, N) {
        while (sz > 1 && ccw(hull[sz - 2], hull[sz - 1], poly[i]) <= 0)
            --sz;
        hull[sz++] = poly[i];
    }
    hull[sz] = hull[0];
}
ll solve1() {
    int it[4];
    loop(i, 3) it[i] =  find(poly, poly + N, hull[i]) - poly;
    it[3] = it[0];

    ll ret = area(hull[0], hull[1], hull[2]), tri = LLONG_MAX;
    loop(i, 3) loop(j, N) if (j != it[i] && j != it[i + 1])
        tri = min(tri, area(hull[i], hull[i + 1], poly[j]));
    return ret - tri;
}
ll solve2() {
    ll ret = 0;
    loop(i, sz - 2) {
        int p1 = i + 1, p2 = i + 3;
        for (int j = i + 2; j < sz; ++j) {
            while (p1 + 1 ^ j && area(hull[i], hull[p1], hull[j]) < area(hull[i], hull[p1 + 1], hull[j])) ++p1;
            while ((p2 + 1) % sz ^ i && area(hull[j], hull[p2], hull[i]) < area(hull[j], hull[p2 + 1], hull[i])) p2 = (p2 + 1) % sz;
            ret = max(ret, area(hull[i], hull[p1], hull[j]) + area(hull[j], hull[p2], hull[i]));
        }
    }
    return ret;
}
void output() {
    ll ans;
    if (sz < 3) ans = 0;
    else if (sz == 3) ans = solve1();
    else ans = solve2();
    cout << (ans >> 1) << (ans & 1 ? ".5\n" : "\n");
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        input();
        convex_hull();
        output();
    }
    return 0;
}