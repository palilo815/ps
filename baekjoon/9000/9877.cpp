#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v, w;
    edge(int a, int b, int c): u(a), v(b), w(c) {}
};

const int M = 500;
const int mod = 1 << 9;

int lo[M][M], hi[M][M], parent[mod * mod];
bool src[M][M];
vector<edge> e;

int _find(int u) {
    if (parent[u] < 0) return u;
    return parent[u] = _find(parent[u]);
}
void _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (u == v) return;
    if (parent[u] < parent[v]) swap(u, v);
    parent[v] += parent[u];
    parent[u] = v;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, T; cin >> row >> col >> T;
    loop(i, row) loop(j, col) cin >> hi[i][j];
    loop(i, row) loop(j, col) cin >> src[i][j];

    loop(r, row) loop(c, col) {
        if (c + 1 ^ col) e.emplace_back(r * mod + c, r * mod + c + 1, abs(hi[r][c] - hi[r][c + 1]));
        if (r + 1 ^ row) e.emplace_back(r * mod + c, (r + 1) * mod + c, abs(hi[r][c] - hi[r + 1][c]));
    }
    sort(e.begin(), e.end(), [&](edge & a, edge & b) -> bool {
        return a.w < b.w;
    });

    int N = e.size();
    loop(i, row) fill_n(hi[i], col, N);

    while (1) {
        loop(i, row) memset(parent + i * mod, -1, sizeof(int) * col);
        vector<vector<int>> q(N);
        bool done = true;
        loop(i, row) loop(j, col) if (src[i][j] && lo[i][j] ^ hi[i][j]) {
            q[(lo[i][j] + hi[i][j]) >> 1].emplace_back(i * mod + j);
            done = false;
        }
        if (done) break;

        loop(m, N) {
            _union(e[m].u, e[m].v);
            for (int& i : q[m]) {
                int sz = -parent[_find(i)];
                sz < T ? (lo[i / mod][i % mod] = m + 1) : (hi[i / mod][i % mod] = m);
            }
        }
    }

    long long ans = 0;
    loop(i, row) loop(j, col) if (src[i][j])
        ans += e[lo[i][j]].w;
    cout << ans;
    return 0;
}