#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct elem {
    int a, b, c;
    elem(int a, int b, int c): a(a), b(b), c(c) {}
};

const int mxN = 2e3;
const int mxP = 2e5;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mxN + 2][mxN + 2];
int area[mxN + 2][mxN + 2];

int par[mxP + 1];
int qu[mxP], qv[mxP], lo[mxP], hi[mxP];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int H, W, P, Q;
    cin >> H >> W >> P >> Q;
    for (int i = 1; i <= H; ++i)
        cin >> (mat[i] + 1);

    memset(mat[0] + 1, '#', W);
    memset(mat[H + 1] + 1, '#', W);
    for (int i = 1; i <= H; ++i)
        mat[i][0] = mat[i][W + 1] = '#';

    queue<elem> q;
    for (int i = 1, r, c; i <= P; ++i) {
        cin >> r >> c;
        area[r][c] = i;
        q.emplace(r, c, i);
    }

    vector<elem> edges;
    for (int d = 0; !q.empty(); ++d) {
        for (int cnt = q.size(); cnt; --cnt) {
            auto [r, c, id] = q.front(); q.pop();

            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (mat[R][C] == '#' || area[R][C] == id) continue;
                if (area[R][C])
                    edges.emplace_back(id, area[R][C], d * 2 + (id > area[R][C]));
                else {
                    area[R][C] = id;
                    q.emplace(R, C, id);
                }
            }
        }
    }

    sort(edges.begin(), edges.end(), [&](auto & a, auto & b) {
        return a.c < b.c;
    });
    memset(par + 1, -1, sizeof(int) * P);

    vector<elem> mst;
    for (auto& e : edges) {
        int u = _find(e.a), v = _find(e.b);
        if (u ^ v) {
            par[u] = v;
            mst.emplace_back(e);
            if (mst.size() == P - 1) break;
        }
    }

    loop(i, Q) cin >> qu[i] >> qv[i];
    int N = min(P - 1, (int)mst.size());
    fill(hi, hi + Q, N);

    for (;;) {
        vector<vector<int>> vt(N);
        bool done = true;

        loop(i, Q) if (lo[i] ^ hi[i]) {
            vt[(lo[i] + hi[i]) >> 1].emplace_back(i);
            done = false;
        }
        if (done) break;

        memset(par + 1, -1, sizeof(int) * P);

        loop(m, N) {
            int u = _find(mst[m].a), v = _find(mst[m].b);
            par[u] = v;
            for (int& i : vt[m]) {
                u = _find(qu[i]), v = _find(qv[i]);
                u ^ v ? (lo[i] = m + 1) : (hi[i] = m);
            }
        }
    }

    loop(i, Q) cout << (lo[i] == N ? -1 : mst[lo[i]].c) << '\n';
    return 0;
}