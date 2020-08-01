#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;

const int mxN = 1e5 + 1;

int x[mxN], y[mxN];

int ccw(int u, int m, int v) {
    ll ret = (ll)(x[m] - x[u]) * (y[v] - y[u]) -
             (ll)(y[m] - y[u]) * (x[v] - x[u]);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> x[i] >> y[i];

    int u, v; cin >> u >> v;
    bool rev = false;
    if (u > v) {
        swap(u, v);
        rev = true;
    }
    if (!u) {
        x[N] = x[0], y[N] = y[0];
        u = v; v = N; rev = !rev;
    }

    vector<int> hull;
    for (int i = u; i <= v; ++i) {
        while (hull.size() > 1 && ccw(hull[hull.size() - 2], hull[hull.size() - 1], i) >= 0)
            hull.pop_back();
        hull.emplace_back(i);
    }
    if (*hull.begin() == N) *hull.begin() = 0;
    if (*hull.rbegin() == N) *hull.rbegin() = 0;
    if (rev) reverse(hull.begin(), hull.end());

    cout << hull.size() << '\n';
    for (int x : hull) cout << x << ' ';
    return 0;
}