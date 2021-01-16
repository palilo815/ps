#include <bits/stdc++.h>
using namespace std;

const int M = 102;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

char a[M][M];
int row, col, dist[3][M][M];

void bfs(int sr, int sc, int dist[][M]) {
    deque<pair<int, int>> dq;
    dist[sr][sc] = 0;
    dq.emplace_back(sr, sc);

    while (!dq.empty()) {
        auto [r, c] = dq.front();
        dq.pop_front();

        for (int i = 0; i < 4; ++i) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R == -1 || R == row + 2 || C == -1 || C == col + 2 || ~dist[R][C] || a[R][C] == '*') continue;

            if (a[R][C] == '#') {
                dist[R][C] = dist[r][c] + 1;
                dq.emplace_back(R, C);
            } else {
                dist[R][C] = dist[r][c];
                dq.emplace_front(R, C);
            }
        }
    }
}
void solve() {
    cin >> row >> col;
    int cr1 = 0, cc1 = 0, cr2 = 0, cc2 = 0;

    memset(a[0], '.', col + 2);
    memset(a[row + 1], '.', col + 2);
    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            cin >> a[i][j];
            if (a[i][j] == '$')
                cr1 ? (cr2 = i, cc2 = j) : (cr1 = i, cc1 = j);
        }
        a[i][0] = a[i][col + 1] = '.';
    }

    memset(dist, -1, sizeof(dist));

    bfs(0, 0, dist[0]);
    bfs(cr1, cc1, dist[1]);
    bfs(cr2, cc2, dist[2]);

    int ans = INT_MAX;
    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            if (~dist[0][i][j]) {
                int d = dist[0][i][j] + dist[1][i][j] + dist[2][i][j];
                if (a[i][j] == '#') d -= 2;
                ans = min(ans, d);
            }
    cout << ans << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}