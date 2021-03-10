#include <bits/stdc++.h>
using namespace std;

struct dinic {
    dinic(int _n, int _src, int _sink) : adj(_n), level(_n), ptr(_n),
                                         src(_src), sink(_sink) {}

    void add_edge(int u, int v, int c) {
        adj[u].emplace_back(v, c, adj[v].size());
        adj[v].emplace_back(u, 0, adj[u].size() - 1);
    }
    int64_t flow() {
        int64_t ret = 0;
        for (int f; bfs();) {
            fill(ptr.begin(), ptr.end(), 0);
            while ((f = dfs(0, INT_MAX))) ret += f;
        }
        return ret;
    }

private:
    struct edge {
        int v, capa, rev;
        edge(int v, int capa, int rev) : v(v), capa(capa), rev(rev) {}
    };
    const int src, sink;
    vector<vector<edge>> adj;
    vector<int> level, ptr;

    int bfs() {
        fill(level.begin(), level.end(), 0);
        level[src] = 1;

        queue<int> q;
        q.emplace(src);

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto& [v, capa, _] : adj[u])
                if (capa && !level[v]) {
                    level[v] = level[u] + 1;
                    q.emplace(v);
                }
        }
        return level[sink];
    }
    int dfs(int u, int f) {
        if (u == sink) return f;
        for (int &i = ptr[u], sz = adj[u].size(); i < sz; ++i) {
            auto& [v, capa, rev] = adj[u][i];
            if (capa && level[u] + 1 == level[v])
                if (int d = dfs(v, min(f, capa)); d) {
                    capa -= d;
                    adj[v][rev].capa += d;
                    return d;
                }
        }
        return 0;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    const int src = 0, sink = n + m + 1;
    // 1 ~ n : 사람
    // n + 1 ~ n + m: 서점

    dinic mf(n + m + 2, src, sink);
    for (int i = 1, c; i <= n; ++i) {
        cin >> c;
        mf.add_edge(src, i, c);
    }
    for (int i = n + 1, c; i <= n + m; ++i) {
        cin >> c;
        mf.add_edge(i, sink, c);
    }
    for (int i = n + 1, c; i <= n + m; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> c;
            mf.add_edge(j, i, c);
        }

    cout << mf.flow();
}