#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k, a, b;
    cin >> n >> m >> k >> a >> b, --k;

    vector<vector<int>> adj(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> step(n, -1);
    step[k] = 0;

    queue<int> q;
    q.emplace(k);
    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto& v : adj[u])
            if (step[v] == -1) {
                step[v] = step[u] + 1;
                q.emplace(v);
            }
    }

    vector<vector<int>> vtx = adj;
    vector<bool> neighbor(n);

    vector<int> jump(n, -1);
    jump[k] = 0;

    q.emplace(k);
    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto& v : adj[u])
            neighbor[v] = true;

        for (const auto& via : adj[u])
            vtx[via].erase(remove_if(vtx[via].begin(), vtx[via].end(), [&](auto& v) {
                               if (neighbor[v] || ~jump[v]) return false;
                               jump[v] = jump[u] + 1;
                               q.emplace(v);
                               return true;
                           }),
                           vtx[via].end());

        for (const auto& v : adj[u])
            neighbor[v] = false;
    }

    for (int i = 0; i < n; ++i)
        cout << min({step[i] * a,
                     (step[i] & 1) * a + (step[i] >> 1) * b,
                     ~jump[i] ? jump[i] * b : INT_MAX})
             << '\n';
}