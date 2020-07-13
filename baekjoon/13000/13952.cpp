#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct p {
    int u, v;
    p(int u = 0, int v = 0) : u(u), v(v) {}
};

const int mov[8][2] = { -1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};
const int max_N = 1e3;
const int max_Q = 3e5;
const int mod = 1024;
const int M = max_N >> 1;

char mat[max_N][max_N];
int N, len[max_N][max_N];
vector<p> e[max_N];

p q[max_Q];
int lo[max_Q], hi[max_Q];

int parent[mod * mod];

int _find(int u) {
    if (~parent[u]) return parent[u] = _find(parent[u]);
    return u;
}
void bfs() {
    queue<pair<int, int>> q;
    memset(len, 0x3f, sizeof(len));
    loop(i, N) loop(j, N) if (mat[i][j] == '#') {
        q.emplace(i, j);
        len[i][j] = -1;
    }

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        loop(i, 8) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R ^ N && ~C && C ^ N && mat[R][C] == '.' && len[R][C] > len[r][c] + 1) {
                len[R][C] = len[r][c] + 1;
                q.emplace(R, C);
            }
        }
    }

    loop(i, N) loop(j, N) if (~len[i][j])
        len[i][j] = min({i, j, N - 1 - i, N - 1 - j, len[i][j]});
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) loop(j, N) cin >> mat[i][j];

    bfs();

    loop(i, N) loop(j, N) if (~len[i][j]) {
        if (j + 1 ^ N && ~len[i][j + 1])
            e[M - 1 - min(len[i][j], len[i][j + 1])].emplace_back(i * mod + j, i * mod + j + 1);
        if (i + 1 ^ N && ~len[i + 1][j])
            e[M - 1 - min(len[i][j], len[i + 1][j])].emplace_back(i * mod + j, (i + 1) * mod + j);
    }

    int Q; cin >> Q;
    loop(i, Q) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        q[i].u = --r1 * mod + --c1, q[i].v = --r2 * mod + --c2;
    }
    fill_n(hi, Q, M);
    /*
    length:0 -> square 1        [499]   1
    length:1 -> square 3
    length:2 -> square 5
    ...
    ...                         [1]     997
    length:499 -> square 999    [0]     999
    */
    while (1) {
        vector<vector<int>> vt(M);
        bool done = true;
        loop(i, Q) if (lo[i] ^ hi[i]) {
            vt[(lo[i] + hi[i]) >> 1].emplace_back(i);
            done = false;
        }
        if (done) break;

        memset(parent, -1, sizeof(parent));
        loop(m, M) {
            for (auto [u, v] : e[m]) {
                u = _find(u), v = _find(v);
                if (u ^ v) parent[u] = v;
            }
            for (int& i : vt[m])
                _find(q[i].u) ^ _find(q[i].v) ? (lo[i] = m + 1) : (hi[i] = m);
        }
    }
    loop(i, Q) cout << (lo[i] == M ? 0 : max_N - 1 - (lo[i] << 1)) << '\n';
    return 0;
}