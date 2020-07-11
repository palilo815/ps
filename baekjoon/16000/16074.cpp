#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;
struct edge {
    int u, v, w;
    edge(int a, int b, int c): u(a), v(b), w(c) {}
};

const int M = 500;
const int max_Q = 1e5;

int mat[M][M];
int lo[max_Q], hi[max_Q], parent[M][M];
vector<edge> e;
p q[max_Q];

int _find(int u) {
    int r = u / M, c = u % M;
    if (parent[r][c] < 0) return u;
    return parent[r][c] = _find(parent[r][c]);
}
void _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (u ^ v) parent[u / M][u % M] = v;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, Q; cin >> row >> col >> Q;
    loop(i, row) loop(j, col) cin >> mat[i][j];
    loop(r, row) loop(c, col) {
        int B = r * M + c;
        if (c + 1 ^ col) e.emplace_back(B, B + 1, max(mat[r][c], mat[r][c + 1]));
        if (r + 1 ^ row) e.emplace_back(B, B + M, max(mat[r][c], mat[r + 1][c]));
    }
    sort(e.begin(), e.end(), [&](edge & a, edge & b) -> bool {
        return a.w < b.w;
    });

    int N = e.size();
    fill(hi, hi + Q, N);

    loop(i, Q) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        if (r1 == r2 && c1 == c2) lo[i] = N;
        --r1, --c1, --r2, --c2;
        q[i] = {r1* M + c1, r2* M + c2};
    }

    while (1) {
        loop(i, row) memset(parent[i], -1, sizeof(int) * col);
        vector<vector<int>> vt(N);
        bool done = true;
        loop(i, Q) if (lo[i] ^ hi[i]) {
            vt[(lo[i] + hi[i]) >> 1].emplace_back(i);
            done = false;
        }
        if (done) break;

        loop(m, N) {
            _union(e[m].u, e[m].v);
            for (int& i : vt[m]) {
                int u = _find(q[i].first), v = _find(q[i].second);
                u == v ? (hi[i] = m) : (lo[i] = m + 1);
            }
        }
    }
    loop(i, Q) cout << (lo[i] == N ? mat[q[i].first / M][q[i].first % M] : e[lo[i]].w) << '\n';
    return 0;
}