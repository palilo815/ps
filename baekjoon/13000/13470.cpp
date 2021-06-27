#include <bits/stdc++.h>
using namespace std;

class bipartite_matching {
    const int n, m;
    vector<vector<int>> adj;
    vector<int> match, rev;
    vector<bool> visited;

public:
    bipartite_matching(int _n, int _m) : n(_n), m(_m),
                                         adj(n), match(n, -1), rev(m, -1), visited(n) {}

    void clear() {
        for (auto& vt : adj) vt.clear();
        fill(match.begin(), match.end(), -1);
        fill(rev.begin(), rev.end(), -1);
        fill(visited.begin(), visited.end(), false);
    }
    void add_edge(int u, int v) {
        assert(0 <= u and u < n and 0 <= v and v < m);
        adj[u].emplace_back(v);
    }
    int maximum_matching() {
        for (bool update = true; update;) {
            fill(visited.begin(), visited.end(), false);
            update = false;

            for (int i = 0; i < n; ++i)
                if (match[i] == -1 && dfs(i))
                    update = true;
        }
        return n - count(match.begin(), match.end(), -1);
    }
    vector<int> minimum_vertex_cover() {
        vector<bool> check(m);
        auto bfs = [&](int src) {
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

        vector<int> ret;
        ret.reserve(n - count(match.begin(), match.end(), -1));

        for (int i = 0; i < n; ++i)
            if (!visited[i])
                ret.emplace_back(i);
        for (int i = 0; i < m; ++i)
            if (check[i])
                ret.emplace_back(~i);

        return ret;
    }

private:
    bool dfs(int u) {
        visited[u] = true;
        for (const auto& v : adj[u]) {
            if (rev[v] == -1 || (!visited[rev[v]] && dfs(rev[v]))) {
                match[u] = v, rev[v] = u;
                return true;
            }
        }
        return false;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<pair<int, int>> a(n), b(n);
    for (auto& [x, y] : a) cin >> x >> y;
    for (auto& [x, y] : b) cin >> x >> y;

    auto parametric = [&](auto lo, auto hi) {
        bipartite_matching graph(n, n);
        auto f = [&](auto mid) -> bool {
            graph.clear();
            for (int i = 0; i < n; ++i) {
                bool no_edge = true;
                for (int j = 0; j < n; ++j)
                    if (abs(a[i].first - b[j].first) + abs(a[i].second - b[j].second) <= mid) {
                        graph.add_edge(i, j);
                        no_edge = false;
                    }
                if (no_edge) return false;
            }
            return graph.maximum_matching() == n;
        };

        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };

    cout << parametric(0, int(4e8));
}