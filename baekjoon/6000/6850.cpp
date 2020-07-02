#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

const int M = 10000;

p poly[M], axis;

int ccw(p& a, p& b, p& c) {
    int ret = (b.x - a.x) * (c.y - a.y) -
              (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int dist(p& v) {
    int dx = axis.x - v.x, dy = axis.y - v.y;
    return dx * dx + dy * dy;
}
int area(p& a, p& b) {
    int ret = (a.x - axis.x) * (b.y - axis.y) -
              (a.y - axis.y) * (b.x - axis.x);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> poly[i].x >> poly[i].y;

    axis = *min_element(poly, poly + N, [](p & a, p & b) -> bool {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    sort(poly, poly + N, [](p & a, p & b) -> bool {
        int ret = ccw(axis, a, b);
        return ret ? ret == 1 : dist(a) < dist(b);
    });

    vector<p> stk;
    loop(i, N) {
        while (stk.size() > 1 && ccw(stk[stk.size() - 2], stk[stk.size() - 1], poly[i]) <= 0)
            stk.pop_back();
        stk.emplace_back((poly[i]));
    }

    if (stk.size() < 3) {cout << '0'; return 0;}

    long long ans = 0;
    for (int i = 1; i < stk.size() - 1; ++i)
        ans += area(stk[i], stk[i + 1]);
    cout << ans / 100;
    return 0;
}