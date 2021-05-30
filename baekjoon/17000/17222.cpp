#include <bits/stdc++.h>
using namespace std;

template <typename flow_t>
class dinitz {
    struct edge {
        int v, rev;
        flow_t capa;
        edge(int _v, int _rev, flow_t _capa) : v(_v), rev(_rev), capa(_capa) {}
    };

public:
    dinitz(int _n) : n(_n), adj(_n), level(_n), ptr(_n) {}

    void add_edge(int u, int v, flow_t c) {
        assert(0 <= u and u < n and 0 <= v and v < n);
        adj[u].emplace_back(v, adj[v].size(), c);
        adj[v].emplace_back(u, adj[u].size() - 1, 0);
    }
    flow_t max_flow(int s, int t) {
        assert(0 <= s and s < n and 0 <= t and t < n);
        src = s, sink = t;

        flow_t ret = 0;
        for (flow_t f; bfs();) {
            fill(ptr.begin(), ptr.end(), 0);
            while ((f = dfs(src, FLOW_MAX))) ret += f;
        }
        return ret;
    }

private:
    const flow_t FLOW_MAX = numeric_limits<flow_t>::max();
    const int n;
    int src = -1, sink = -1;

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

            for (const auto& [v, rev, capa] : adj[u])
                if (capa && !level[v]) {
                    level[v] = level[u] + 1;
                    q.emplace(v);
                }
        }
        return level[sink];
    }
    flow_t dfs(int u, flow_t f) {
        if (u == sink) return f;
        for (int &i = ptr[u], sz = adj[u].size(); i < sz; ++i) {
            auto& [v, rev, capa] = adj[u][i];
            if (capa && level[u] + 1 == level[v])
                if (flow_t d = dfs(v, min(f, capa)); d) {
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

    vector<int> c(n + m);
    for (auto& x : c) cin >> x;

    const int s = n + m, t = n + m + 1;
    dinitz<int64_t> flow(n + m + 2);

    for (int i = 0; i < n; ++i)
        flow.add_edge(i, t, LLONG_MAX);
    for (int i = n; i < n + m; ++i)
        flow.add_edge(s, i, c[i]);

    for (int u = n, k, v; u < n + m; ++u)
        for (cin >> k; k--;) {
            cin >> v, --v;
            flow.add_edge(u, v, c[v]);
        }

    cout << flow.max_flow(s, t);
}