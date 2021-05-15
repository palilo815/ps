#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<string> name(n);
    for (auto& x : name) cin >> x;

    unordered_map<string, int> index;
    for (int i = 0; i < n; ++i)
        index[name[i]] = i;

    vector<vector<int>> adj(n);
    for (int u = 0, m; u < n; ++u) {
        string s;
        cin >> s >> m;
        while (m--) {
            cin >> s;
            for (bool go = true; go;) {
                cin >> s;
                if (s.back() == ',')
                    s.pop_back();
                else
                    go = false;

                int v = index[s];
                adj[u].emplace_back(v);
            }
        }
    }

    int ans = INT_MAX;
    vector<int> dist(n), par(n), path;

    auto bfs = [&](int s) {
        fill(par.begin(), par.end(), -1);
        fill(dist.begin(), dist.end(), -1);
        dist[s] = 0;

        queue<int> q;
        q.emplace(s);

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            if (dist[u] == ans) return;

            for (const auto& v : adj[u]) {
                if (v == s) {
                    path.resize(ans = dist[u] + 1);
                    for (int i = ans, x = u; i--; x = par[x])
                        path[i] = x;
                    return;
                } else if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    par[v] = u;
                    q.emplace(v);
                }
            }
        }
    };

    for (int i = 0; i < n; ++i)
        bfs(i);

    if (ans == INT_MAX) return cout << "SHIP IT", 0;
    for (const auto& x : path)
        cout << name[x] << ' ';
}