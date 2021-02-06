#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

constexpr int mxN = 1e3;

struct edge {
    int u, v, w;
    edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

struct disjoint_set {
    vector<int> par, dist;
    disjoint_set(int n) : par(n, -1), dist(n) {}
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    void merge(int u, int v, int w) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;

        dist[v] = w;
    }
    int query(int u, int v) {
        int ret = -1;
        for (; u != v && ret; u = par[u]) {
            if (dist[u] < dist[v]) swap(u, v);
            ret = dist[u];
        }
        return ret ? (ret << 1) - 1 : 0;
    }
};

char mat[mxN][mxN];
int dist[mxN][mxN];

void bfs(int n) {
    queue<pair<int, int>> q;
    memset(dist, 0x3f, sizeof(dist));
    loop(i, n) loop(j, n) if (mat[i][j] == '#') {
        q.emplace(i, j);
        dist[i][j] = 0;
    }

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int R = r - 1; R <= r + 1; ++R)
            for (int C = c - 1; C <= c + 1; ++C)
                if (~R && R != n && ~C && C != n && mat[R][C] == '.' && dist[R][C] > dist[r][c] + 1) {
                    dist[R][C] = dist[r][c] + 1;
                    q.emplace(R, C);
                }
    }
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    loop(i, n) loop(j, n) cin >> mat[i][j];

    bfs(n);

    loop(i, n) loop(j, n) if (~dist[i][j])
        dist[i][j] = min({i + 1, j + 1, n - i, n - j, dist[i][j]});

    vector<edge> e;
    loop(i, n) loop(j, n) {
        if (dist[i][j] == -1) continue;
        if (j != n - 1 && ~dist[i][j + 1])
            e.emplace_back(i * n + j, i * n + (j + 1), min(dist[i][j], dist[i][j + 1]));
        if (i != n - 1 && ~dist[i + 1][j])
            e.emplace_back(i * n + j, (i + 1) * n + j, min(dist[i][j], dist[i + 1][j]));
    }

    sort(e.begin(), e.end(), [&](auto& a, auto& b) {
        return a.w > b.w;
    });

    disjoint_set dsu(n * n);
    for (const auto [u, v, w] : e)
        dsu.merge(u, v, w);

    int q;
    cin >> q;

    for (int r1, c1, r2, c2; q--;) {
        cin >> r1 >> c1 >> r2 >> c2;
        --r1, --c1, --r2, --c2;
        cout << dsu.query(r1 * n + c1, r2 * n + c2) << '\n';
    }
}