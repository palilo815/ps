#include <bits/stdc++.h>

class BipartiteMatching {
    const int n, m;
    std::vector<std::vector<int>> adj;
    std::vector<int> match, rev;
    std::vector<int8_t> visited;

public:
    BipartiteMatching(int n, int m) : n(n), m(m), adj(n), match(n, -1), rev(m, -1), visited(n) {}

    auto add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < m);
        adj[u].emplace_back(v);
    }

    auto maximum_matching() {
        for (bool update = true; update;) {
            fill(visited.begin(), visited.end(), false);
            update = false;
            for (int i = 0; i < n; ++i) {
                if (match[i] == -1 && dfs(i)) {
                    update = true;
                }
            }
        }
        return n - count(match.begin(), match.end(), -1);
    }

private:
    auto dfs(int u) -> bool {
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

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<tuple<int, int, int>> ver, hor;
    for (int i = n, x0, y0, x1, y1; i--;) {
        cin >> x0 >> y0 >> x1 >> y1;
        if (x0 > x1) swap(x0, x1);
        if (y0 > y1) swap(y0, y1);
        if (x0 == x1) {
            ver.emplace_back(x0, y0, y1);
        } else {
            hor.emplace_back(y0, x0, x1);
        }
    }
    BipartiteMatching bm(ver.size(), hor.size());
    for (int u = 0; const auto& [x, y0, y1] : ver) {
        for (int v = 0; const auto& [y, x0, x1] : hor) {
            if (x0 <= x && x <= x1 && y0 <= y && y <= y1) {
                bm.add_edge(u, v);
            }
            ++v;
        }
        ++u;
    }
    cout << n - bm.maximum_matching();
}
