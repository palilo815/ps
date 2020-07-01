#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using ll = long long;
using p = pair<int, int>;

const int M = 100000;

p poly[M], datum;

int ccw(p& a, p& b, p& c) {
    ll ret = 1LL * (b.x - a.x) * (c.y - a.y) -
             1LL * (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
ll dist(p& v) {
    ll dx = datum.x - v.x, dy = datum.y - v.y;
    return dx * dx + dy * dy;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> poly[i].x >> poly[i].y;

    datum = *min_element(poly, poly + N, [](p & a, p & b) -> bool {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    sort(poly, poly + N, [](p & a, p & b) -> bool {
        int ret = ccw(datum, a, b);
        return ret ? ret == 1 : dist(a) < dist(b);
    });

    vector<p> stk;
    loop(i, N) {
        while (stk.size() > 1 && ccw(stk[stk.size() - 2], stk[stk.size() - 1], poly[i]) <= 0)
            stk.pop_back();
        stk.emplace_back((poly[i]));
    }
    cout << stk.size();
    return 0;
}