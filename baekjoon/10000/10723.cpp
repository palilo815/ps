#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct edge {
    int u, v, w;
};

const int mx = 2e3;

int par[mx];
vector<edge> e;

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
void solve() {
    int N, M; cin >> N >> M;

    e.resize(N - 1);
    int id = 0;
    for (auto& [u, v, w] : e) {
        u = ++id;
        cin >> v >> w;
    }

    sort(e.begin(), e.end(), [&](auto & a, auto & b) {
        return a.w < b.w;
    });

    ll ans = 0;
    for (edge E; M--;) {
        cin >> E.u >> E.v >> E.w;
        e.insert(lower_bound(e.begin(), e.end(), E, [&](auto & a, auto & b) {
            return a.w < b.w;
        }), E);

        memset(par, -1, sizeof(int) * N);
        ll mst = 0;
        int cnt = N - 1;
        for (auto [u, v, w] : e) {
            u = _find(u), v = _find(v);
            if (u ^ v) {
                mst += w;
                par[u] = v;
                if (--cnt == 0) break;
            }
        }
        ans ^= mst;
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}