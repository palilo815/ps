#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 0x3f3f3f3f;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, q;
    cin >> n >> m >> q;

    vector<pair<int, int>> edge(m);
    for (auto& [u, v] : edge) cin >> u >> v, --u, --v;

    vector<bool> erased(m);
    vector<int> query(q);
    for (auto& x : query) {
        char type;
        cin >> type >> x, --x;
        type == 'U' ? (erased[x] = true) : (x = ~x);
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i)
        if (!erased[i])
            adj[edge[i].first].emplace_back(edge[i].second);

    vector dist(n, INF);
    dist[0] = 0;

    auto bfs = [&](int s) {
        queue<int> q;
        q.emplace(s);

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto& v : adj[u])
                if (dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    q.emplace(v);
                }
        }
    };

    bfs(0);

    vector<int> ans;
    ans.reserve(q - count(erased.begin(), erased.end(), true));

    // query[i] =  x -> x번 간선 재생성
    // qeury[i] = ~x -> 0 to x 최단경로
    for (int i = q; i--;)
        if (query[i] < 0) ans.emplace_back(dist[~query[i]] == INF ? -1 : dist[~query[i]]);
        else {
            adj[edge[query[i]].first].emplace_back(edge[query[i]].second);
            bfs(edge[query[i]].first);
        }

    reverse(ans.begin(), ans.end());

    for (const auto& x : ans)
        cout << x << '\n';
}