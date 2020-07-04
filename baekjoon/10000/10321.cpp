#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

const int M = 1000;

int N, sz, ans;
p poly[M], hull[M];

int ccw(p& a, p& b, p& c) {
    int ret = (b.x - a.x) * (c.y - a.y) -
              (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int area(int i, int j, int k) {
    p& a = hull[i], & b = hull[j], & c = hull[k];
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
int dist(p& v) {
    int dx = poly[0].x - v.x, dy = poly[0].y - v.y;
    return dx * dx + dy * dy;
}
void input() {
    cin >> N;
    loop(i, N) cin >> poly[i].x >> poly[i].y;
}
void convex_hull() {
    swap(poly[0], *min_element(poly, poly + N));
    sort(poly, poly + N, [&](p & a, p & b) -> bool {
        int ret = ccw(poly[0], a, b);
        return ret ? ret == 1 : dist(a) < dist(b);
    });

    sz = 0;
    loop(i, N) {
        while (sz > 1 && ccw(hull[sz - 2], hull[sz - 1], poly[i]) <= 0)
            --sz;
        hull[sz++] = poly[i];
    }
}
int solve() {
    hull[sz] = hull[0];
    int ret = 0;
    loop(i, sz - 2) {
        int p1 = i + 1, p2 = i + 3;
        for (int j = i + 2; j < sz; ++j) {
            while (p1 + 1 ^ j && area(i, p1, j) < area(i, p1 + 1, j)) ++p1;
            while ((p2 + 1) % sz ^ i && area(j, p2, i) < area(j, p2 + 1, i)) p2 = (p2 + 1) % sz;
            ret = max(ret, area(i, p1, j) + area(j, p2, i));
        }
    }
    return ret;
}
void output() {
    if (sz < 3) ans = 0;
    else if (sz == 3) ans = area(0, 1, 2);
    else ans = solve();
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