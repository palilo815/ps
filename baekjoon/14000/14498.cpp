#include <bits/stdc++.h>
using namespace std;

struct query {
    int x, y, op;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;

    vector<query> q(k);
    for (auto& [x, y, op] : q)
        cin >> x >> y >> op, --x, --y;

    vector<vector<int>> adj(k);
    for (int i = 0; i < k - 1; ++i)
        for (int j = i + 1; j < k; ++j)
            if (q[i].op != q[j].op && (q[i].x == q[j].x || q[i].y == q[j].y))
                q[i].op ? adj[j].emplace_back(i) : adj[i].emplace_back(j);

    vector<int> match(k, -1);
    vector<bool> visited(k);
    function<bool(int)> dfs = [&](int u) {
        visited[u] = true;
        for (const auto& v : adj[u]) {
            if (match[v] == -1 || (!visited[match[v]] && dfs(match[v]))) {
                match[u] = v, match[v] = u;
                return true;
            }
        }
        return false;
    };

    for (bool update = true; update;) {
        fill(visited.begin(), visited.end(), false);
        update = false;

        for (int i = 0; i < k; ++i)
            if (match[i] == -1 && dfs(i))
                update = true;
    }
    cout << (k - count(match.begin(), match.end(), -1) >> 1);
}