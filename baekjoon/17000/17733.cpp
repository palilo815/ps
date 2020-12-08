#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 2e3;
const int mxP = 2e5;

char mat[mxN + 2][mxN + 2];
int area[mxN + 2][mxN + 2], par[mxP + 1], dist[mxP + 1];

void merge(int u, int v, int w) {
    while (par[u] >= 0) u = par[u];
    while (par[v] >= 0) v = par[v];
    if (u == v) return;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;
    dist[v] = w;
}
void bfs(int P) {
    const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};
    memset(par + 1, -1, sizeof(int) * P);
    memset(dist + 1, 0x3f, sizeof(int) * P);

    queue<pair<int, int>> q;
    for (int i = 1, r, c; i <= P; ++i) {
        cin >> r >> c;
        area[r][c] = i;
        q.emplace(r << 11 | c, i);
    }

    for (int d = 0; !q.empty(); ++d) {
        vector<pair<int, int>> tmp;
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
                } else if (id < area[R][C])
                    merge(id, area[R][C], d << 1);
                else if (id > area[R][C])
                    tmp.emplace_back(id, area[R][C]);
            }
        }
        for (auto& e : tmp)
            merge(e.first, e.second, d << 1 | 1);
    }
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

    bfs(P);

    for (int u, v, ans; Q--;) {
        for (cin >> u >> v; u != v && u > 0; u = par[u]) {
            if (dist[u] > dist[v]) swap(u, v);
            ans = dist[u];
        }
        cout << (u > 0 ? ans : -1) << '\n';
    }
}