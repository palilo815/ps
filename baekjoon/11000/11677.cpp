#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int A, B, n, m;
    cin >> A >> B >> n >> m;

    vector<vector<int>> adj(n), rev(n);
    vector<int> in(n), out(n);
    for (int u, v; m--;) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
        ++out[u], ++in[v];
    }

    vector<bitset<5000>> upper_set(n), lower_set(n);
    auto topological_sort = [&](vector<vector<int>>& g, vector<bitset<5000>>& st, vector<int>& deg) {
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (!deg[i])
                q.emplace(i);

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            st[u][u] = true;
            for (const auto& v : g[u]) {
                if (--deg[v] == 0)
                    q.emplace(v);
                st[v] |= st[u];
            }
        }
    };
    topological_sort(adj, upper_set, in);
    topological_sort(rev, lower_set, out);

    cout << count_if(lower_set.begin(), lower_set.end(), [&](auto& x) { return int(x.count()) > n - A; }) << '\n'
         << count_if(lower_set.begin(), lower_set.end(), [&](auto& x) { return int(x.count()) > n - B; }) << '\n'
         << count_if(upper_set.begin(), upper_set.end(), [&](auto& x) { return int(x.count()) > B; });
}