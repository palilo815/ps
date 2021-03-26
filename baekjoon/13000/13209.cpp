#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<vector<int>> adj(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> par(n, -1), ord(n);
    par[0] = -2;

    auto bfs = [&]() {
        queue<int> q;
        q.emplace(0);

        for (int i = n; i--;) {
            const auto u = q.front();
            q.pop();

            ord[i] = u;
            for (const auto& v : adj[u])
                if (par[v] == -1) {
                    par[v] = u;
                    q.emplace(v);
                }
        }
    };
    bfs();

    vector<int64_t> kid, sz(n);
    kid.reserve(n);

    auto valid = [&](int64_t mid) {
        int cnt = k;
        for (const auto& u : ord) {
            kid.clear();
            for (const auto& v : adj[u])
                if (v != par[u])
                    kid.emplace_back(sz[v]);

            sort(kid.begin(), kid.end());

            int i = 0;
            for (sz[u] = a[u]; i < int(kid.size()); ++i) {
                if (sz[u] + kid[i] > mid) break;
                sz[u] += kid[i];
            }

            if ((cnt -= int(kid.size()) - i) < 0)
                return false;
        }
        return true;
    };

    int64_t lo = *max_element(a.begin(), a.end()),
            hi = accumulate(a.begin(), a.end(), 0LL);
    while (lo != hi) {
        const auto mid = lo + hi >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << lo << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}