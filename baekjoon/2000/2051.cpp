#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int u = 0, v, cnt; u < n; ++u)
        for (cin >> cnt; cnt--;) {
            cin >> v, --v;
            adj[u].emplace_back(v);
        }

    vector<int> match(n, -1), rev(m, -1);
    vector<bool> visited(n);
    function<bool(int)> dfs = [&](int u) {
        visited[u] = true;
        for (const auto& v : adj[u]) {
            if (rev[v] == -1 || (!visited[rev[v]] && dfs(rev[v]))) {
                match[u] = v, rev[v] = u;
                return true;
            }
        }
        return false;
    };

    for (bool update = true; update;) {
        fill(visited.begin(), visited.end(), false);
        update = false;

        for (int i = 0; i < n; ++i)
            if (match[i] == -1 && dfs(i))
                update = true;
    }

    vector<bool> check(m);
    function<void(int)> bfs = [&](int src) {
        queue<int> q;
        q.emplace(src);
        visited[src] = true;

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto& v : adj[u])
                if (~rev[v] && !visited[rev[v]] && match[u] != v) {
                    check[v] = true;
                    visited[rev[v]] = true;
                    q.emplace(rev[v]);
                }
        }
    };

    fill(visited.begin(), visited.end(), false);
    for (int i = 0; i < n; ++i)
        if (match[i] == -1 && !visited[i])
            bfs(i);

    cout << n - count(match.begin(), match.end(), -1) << '\n';

    cout << count(visited.begin(), visited.end(), false);
    for (int i = 0; i < n; ++i)
        if (!visited[i])
            cout << ' ' << i + 1;
    cout << '\n';

    cout << count(check.begin(), check.end(), true);
    for (int i = 0; i < m; ++i)
        if (check[i])
            cout << ' ' << i + 1;
}