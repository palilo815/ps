#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, s;
    cin >> n >> s;

    vector<vector<int>> adj(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> par(n, -1), dep(n, -1);
    dep[0] = 0;

    auto bfs = [&]() {
        queue<int> q;
        q.emplace(0);

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto& v : adj[u])
                if (dep[v] == -1) {
                    par[v] = u, dep[v] = dep[u] + 1;
                    q.emplace(v);
                }
        }
    };
    bfs();

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](auto& a, auto& b) {
        return dep[a] > dep[b];
    });

    vector<int> path(n), kids(n);
    auto valid = [&](int len) {
        int cnt = s;
        for (const auto& u : idx) {
            int sz = 1;
            for (const auto& v : adj[u])
                if (v != par[u])
                    kids[sz++] = path[v] + 1;

            sort(kids.begin() + 1, kids.begin() + sz);
            for (; sz != 1 && kids[sz - 1] + kids[sz - 2] > len; --sz)
                if (--cnt == -1)
                    return false;

            path[u] = kids[sz - 1];
        }
        return true;
    };

    int lo = 0, hi = n - 1;
    while (lo != hi) {
        int mid = lo + hi >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << lo;
}