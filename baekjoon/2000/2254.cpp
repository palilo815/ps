#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using ll = long long;
using p = pair<int, int>;

const int M = 1000;

int N;
p poly[M + 1], axis, prison;

int ccw(p& a, p& b, p& c) {
    ll ret = 1LL * (b.x - a.x) * (c.y - a.y) -
             1LL * (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
vector<p> convex_hull() {
    vector<p> ret;
    auto pos = min_element(poly, poly + N);
    swap(poly[0], *pos);
    axis = poly[0];

    sort(poly + 1, poly + N, [](p & a, p & b) -> bool {
        return ccw(axis, a, b) == 1;
    });
    loop(i, N) {
        while (ret.size() > 1 && ccw(ret[ret.size() - 2], ret[ret.size() - 1], poly[i]) < 0)
            ret.pop_back();
        ret.emplace_back((poly[i]));
    }

    for (p& point : ret)
        if (point == prison) {
            ret.clear();
            break;
        }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> prison.x >> prison.y;
    loop(i, N) cin >> poly[i].x >> poly[i].y;
    poly[N++] = prison;

    int ans = 0;
    while (1) {
        auto vt = convex_hull();
        if (vt.size() < 3) break;
        ++ans;

        N = set_difference(poly, poly + N, vt.begin(), vt.end(), poly, [](p & a, p & b) -> bool {
            return ccw(axis, a, b) == 1;
        }) - poly;
    }
    cout << ans;
    return 0;
}