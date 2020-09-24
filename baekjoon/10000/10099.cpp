#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, r, c;
    elem(int d, int r, int c) : d(d), r(r), c(c) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e3 + 2;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

char mat[mxN][mxN];
int N, M, to_wall[mxN][mxN], dist[mxN][mxN], nxt[mxN][mxN][4];

void bfs() {
    memset(to_wall, -1, sizeof(to_wall));
    queue<pair<int, int>> q;
    for (int i = 0; i < N + 2; ++i)
        for (int j = 0; j < M + 2; ++j)
            if (mat[i][j] == '#')
                q.emplace(i, j);

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (mat[R][C] == '#' || ~to_wall[R][C]) continue;

            to_wall[R][C] = to_wall[r][c] + 1;
            q.emplace(R, C);
        }
    }
}
int dijk(int sr, int sc, int dr, int dc) {
    memset(dist, 0x3f, sizeof(dist));
    dist[sr][sc] = 0;

    priority_queue<elem> pq;
    pq.emplace(0, sr, sc);

    for (; !pq.empty();) {
        auto [d, r, c] = pq.top();
        pq.pop();
        if (dist[r][c] < d) continue;
        if (r == dr && c == dc) return d;

        for (int i = 0; i < 4; ++i) {
            int R = r + mov[i][0], C = c + mov[i][1], D = d + 1;
            if (mat[R][C] != '#' && dist[R][C] > D)
                pq.emplace(dist[R][C] = D, R, C);

            R = r + mov[i][0] * nxt[r][c][i];
            C = c + mov[i][1] * nxt[r][c][i];
            D += to_wall[r][c];

            if (dist[R][C] > D)
                pq.emplace(dist[R][C] = D, R, C);
        }
    }
    return -1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> (mat[i] + 1);
        mat[i][0] = mat[i][M + 1] = '#';
    }
    memset(mat[0], '#', M + 2);
    memset(mat[N + 1], '#', M + 2);

    int sr, sc, dr, dc;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j) {
            if (mat[i][j] == 'S') sr = i, sc = j;
            if (mat[i][j] == 'C') dr = i, dc = j;
        }

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            if (mat[i][j] == '#') nxt[i][j][0] = nxt[i][j][1] = 0;
            else {
                nxt[i][j + 1][1] = nxt[i][j][1] + 1;
                nxt[i + 1][j][0] = nxt[i][j][0] + 1;
            }
    for (int i = N; i; --i)
        for (int j = M; j; --j)
            if (mat[i][j] == '#') nxt[i][j][2] = nxt[i][j][3] = 0;
            else {
                nxt[i][j - 1][2] = nxt[i][j][2] + 1;
                nxt[i - 1][j][3] = nxt[i][j][3] + 1;
            }

    bfs();
    cout << dijk(sr, sc, dr, dc);
    return 0;
}