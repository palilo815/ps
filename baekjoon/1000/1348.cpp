#include <bits/stdc++.h>
using namespace std;

const int mxN = 50;

char mat[mxN][mxN];

struct bipartite_matching {
    vector<vector<pair<int, int>>> adj;
    vector<int> match, rev;
    vector<bool> visited;
    int n, m, limit;

    bipartite_matching(int n, int m) : n(n), m(m) {
        adj.resize(n), match.resize(n), rev.resize(m), visited.resize(n);
    }
    void add_edge(int u, int v, int w) { adj[u].emplace_back(w, v); }
    bool dfs(int u) {
        visited[u] = true;
        for (const auto& [w, v] : adj[u]) {
            if (w > limit) continue;
            if (rev[v] == -1 || (!visited[rev[v]] && dfs(rev[v]))) {
                match[u] = v, rev[v] = u;
                return true;
            }
        }
        return false;
    }
    bool valid(int w) {
        limit = w;
        fill(match.begin(), match.end(), -1);
        fill(rev.begin(), rev.end(), -1);
        for (bool update = true; update;) {
            fill(visited.begin(), visited.end(), false);
            update = false;

            for (int i = 0; i < n; ++i)
                if (match[i] == -1 && dfs(i))
                    update = true;
        }
        return none_of(match.begin(), match.end(), [&](auto& x) { return x == -1; });
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

    vector<int> car, park;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> mat[i][j];
            if (mat[i][j] == 'C') car.emplace_back(i << 8 | j);
            if (mat[i][j] == 'P') park.emplace_back(i << 8 | j);
        }

    bipartite_matching solver(car.size(), park.size());

    constexpr int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};
    vector<vector<int>> dist(n, vector<int>(m));
    int mx = 0;
    auto bfs = [&](const int u) {
        for (auto& vt : dist) fill(vt.begin(), vt.end(), -1);
        dist[car[u] >> 8][car[u] & 0xff] = 0;

        queue<int> q;
        q.emplace(car[u]);

        while (!q.empty()) {
            const auto r = q.front() >> 8, c = q.front() & 0xff;
            q.pop();

            for (int i = 0; i < 4; ++i) {
                const int R = r + mov[i][0], C = c + mov[i][1];
                if (~R && R != n && ~C && C != m && mat[R][C] != 'X' && dist[R][C] == -1) {
                    dist[R][C] = dist[r][c] + 1;
                    q.emplace(R << 8 | C);
                }
            }
        }

        for (int v = 0; v < int(park.size()); ++v)
            if (~dist[park[v] >> 8][park[v] & 0xff]) {
                mx = max(mx, dist[park[v] >> 8][park[v] & 0xff]);
                solver.add_edge(u, v, dist[park[v] >> 8][park[v] & 0xff]);
            }
    };

    for (int i = 0; i < int(car.size()); ++i)
        bfs(i);

    int lo = 0, hi = mx + 1;
    while (lo != hi) {
        int mid = (lo + hi) >> 1;
        solver.valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << (lo == mx + 1 ? -1 : lo);
}