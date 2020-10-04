#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
#define loop_1(i, n) for (int i = 1; i <= n; ++i)
#define u mat[r][c]
#define v mat[R][C]
using namespace std;

const int mxN = 15;
const int mxR = 50 + 2;
const int INF = 0x3f3f3f3f;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

char mat[mxR][mxR];
int row, col, dist[mxN][mxN], dp[1 << mxN][mxN];
bool visited[mxR][mxR];

void dfs(int r, int c, char x) {
    u = x;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (v == 'X') dfs(R, C, x);
    }
}
void bfs(char src) {
    memset(visited, 0, sizeof(visited));

    queue<pair<int, int>> q;
    loop_1(r, row) loop_1(c, col) if (u == src) {
        visited[r][c] = true;
        q.emplace(r, c);
    }
    q.emplace(-1, -1);

    for (int d = 0;;) {
        auto [r, c] = q.front();
        q.pop();
        if (r == -1) {
            if (q.empty()) return;
            ++d, q.emplace(-1, -1);
            continue;
        }

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (v == '.' || visited[R][C]) continue;
            if (v == 'S') {
                visited[R][C] = true;
                q.emplace(R, C);
            } else if (dist[src][v] == INF) {
                dist[src][v] = dist[v][src] = d;
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> row >> col;
    loop_1(i, row) cin >> (mat[i] + 1);

    memset(mat[0] + 1, '.', col);
    memset(mat[row + 1] + 1, '.', col);
    loop_1(i, row) mat[i][0] = mat[i][col + 1] = '.';

    char N = 0;
    loop_1(r, row) loop_1(c, col) if (u == 'X')
        dfs(r, c, N++);

    memset(dist, 0x3f, sizeof(dist));
    loop(i, N) bfs(i);

    loop(k, N) loop(i, N) if (dist[i][k] != INF)
        loop(j, N) if (dist[k][j] != INF)
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    memset(dp, 0x3f, sizeof(dp));
    loop(i, N) dp[1 << i][i] = 0;

    loop(mask, 1 << N) loop(i, N) if (mask & (1 << i))
        loop(j, N) if (!(mask & (1 << j)) && dist[i][j])
            dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + dist[i][j]);

    cout << *min_element(dp[(1 << N) - 1], dp[(1 << N) - 1] + N);
    return 0;
}