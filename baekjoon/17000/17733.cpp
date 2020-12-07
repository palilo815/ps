#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 2e3;
const int mxP = 2e5;

struct edge {
    int u, v, w;
    edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

char mat[mxN + 2][mxN + 2];
int area[mxN + 2][mxN + 2], par[mxP + 1], lo[mxP], hi[mxP];
pair<int, int> q[mxP];

int find(int u) {
    return par[u] < 0 ? u : par[u] = find(par[u]);
}
void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;
}
vector<edge> bfs(int P) {
    const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

    queue<pair<int, int>> q;
    for (int i = 1, r, c; i <= P; ++i) {
        cin >> r >> c;
        area[r][c] = i;
        q.emplace(r << 11 | c, i);
    }

    memset(par + 1, -1, sizeof(int) * P);
    vector<edge> edges;
    vector<pair<int, int>> tmp;
    for (int d = 0; !q.empty(); ++d) {
        for (int cnt = q.size(); cnt; --cnt) {
            int r = q.front().first >> 11,
                c = q.front().first & 0x7ff,
                id = q.front().second;
            q.pop();

            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (mat[R][C] == '#') continue;
                if (!area[R][C]) {
                    area[R][C] = id;
                    q.emplace(R << 11 | C, id);
                } else if (id != area[R][C] && find(id) != find(area[R][C])) {
                    if (id < area[R][C]) {
                        merge(id, area[R][C]);
                        edges.emplace_back(id, area[R][C], d << 1);
                    } else
                        tmp.emplace_back(id, area[R][C]);
                }
            }
        }
        for (auto& e : tmp) {
            int u = find(e.first), v = find(e.second);
            if (u == v) continue;

            edges.emplace_back(e.first, e.second, d << 1 | 1);
            if (par[u] > par[v]) swap(u, v);
            par[u] += par[v];
            par[v] = u;
        }
        tmp.clear();
    }
    return edges;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int H, W, P, Q;
    cin >> H >> W >> P >> Q;
    for (int i = 1; i <= H; ++i)
        cin >> (mat[i] + 1);

    memset(mat[0] + 1, '#', W);
    memset(mat[H + 1] + 1, '#', W);
    for (int i = 1; i <= H; ++i)
        mat[i][0] = mat[i][W + 1] = '#';

    auto edges = bfs(P);
    int N = edges.size();

    loop(i, Q) cin >> q[i].first >> q[i].second;
    fill(hi, hi + Q, N);

    for (;;) {
        vector<vector<int>> check(N);
        bool done = true;

        loop(i, Q) if (lo[i] != hi[i]) {
            check[(lo[i] + hi[i]) >> 1].emplace_back(i);
            done = false;
        }
        if (done) break;

        memset(par + 1, -1, sizeof(int) * P);

        loop(m, N) {
            merge(edges[m].u, edges[m].v);
            for (int& i : check[m])
                find(q[i].first) == find(q[i].second) ? hi[i] = m : lo[i] = m + 1;
        }
    }

    loop(i, Q) cout << (lo[i] == N ? -1 : edges[lo[i]].w) << '\n';
}