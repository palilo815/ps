#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

const int M = 50;

int N;
p poly[M], axis;
vector<p> stk;

int ccw(p& a, p& b, p& c) {
    int ret = (b.x - a.x) * (c.y - a.y) -
              (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int dist(p& v) {
    int dx = axis.x - v.x, dy = axis.y - v.y;
    return dx * dx + dy * dy;
}
void input() {
    cin >> N;
    loop(i, N) cin >> poly[i].x >> poly[i].y;
}
void convex_hull() {
    axis = *min_element(poly, poly + N, [](p & a, p & b) -> bool {
        return a.y == b.y ? a.x < b.x : a.y > b.y;
    });
    sort(poly, poly + N, [](p & a, p & b) -> bool {
        int ret = ccw(axis, a, b);
        return ret ? ret == -1 : dist(a) < dist(b);
    });

    stk.clear();
    loop(i, N) {
        while (stk.size() > 1 && ccw(stk[stk.size() - 2], stk[stk.size() - 1], poly[i]) >= 0)
            stk.pop_back();
        stk.emplace_back(poly[i]);
    }
}
void output() {
    cout << stk.size() << '\n';
    for (p& point : stk)
        cout << point.x << ' ' << point.y << '\n';
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