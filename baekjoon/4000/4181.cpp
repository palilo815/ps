#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using ll = long long;
using p = pair<int, int>;

p axis;

int ccw(p& a, p& b, p& c) {
    ll ret = 1LL * (b.x - a.x) * (c.y - a.y) -
             1LL * (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
ll dist(p& v) {
    ll dx = axis.x - v.x, dy = axis.y - v.y;
    return dx * dx + dy * dy;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    vector<p> poly;
    int N; cin >> N;
    while (N--) {
        int a, b; char c;
        cin >> a >> b >> c;
        if (c == 'Y') poly.emplace_back(a, b);
    }

    axis = *min_element(poly.begin(), poly.end(), [](p & a, p & b) -> bool {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    sort(poly.begin(), poly.end(), [](p & a, p & b) -> bool {
        int ret = ccw(axis, a, b);
        return ret ? ret == 1 : dist(a) < dist(b);
    });


    vector<p> stk;
    for (p& point : poly) {
        while (stk.size() > 1 && ccw(stk[stk.size() - 2], stk[stk.size() - 1], point) < 0)
            stk.pop_back();
        stk.emplace_back(point);
    }
    poly.emplace_back(axis);
    stk.emplace_back(axis);

    for (auto it = poly.begin(), jt = stk.begin(); it != poly.end(); ++it, ++jt)
        if (*it != *jt) {
            auto kt = find(it + 1, poly.end(), *jt);
            reverse(it, kt + 1);
            it = kt;
        }
    poly.pop_back();

    cout << poly.size();
    for (p& point : poly)
        cout << '\n' << point.x << ' ' << point.y;
    return 0;
}