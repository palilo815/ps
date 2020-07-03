#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 20;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0 };

int row, col;
char mat[M][M];
int dist[M][M];
queue<pair<int, int>> q;

int bfs(int s1, int s2) {
    memset(dist, -1, sizeof(dist));
    dist[s1 / col][s1 % col] = dist[s2 / col][s2 % col] = 0;

    q.emplace(s1 / col, s1 % col);
    q.emplace(s2 / col, s2 % col);

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || dist[R][C] != -1)
                continue;
            dist[R][C] = dist[r][c] + 1;
            q.emplace(R, C);
        }
    }

    int ret = 0;
    loop(i, row) loop(j, col) if (mat[i][j] == '1')
        ret = max(ret, dist[i][j]);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> mat[i][j];

    int ans = INT_MAX;
    loop(i, row * col - 1) if (mat[i / col][i % col] == '0')
        for (int j = i + 1; j < row * col; ++j)
            if (mat[j / col][j % col] == '0')
                ans = min(ans, bfs(i, j));
    cout << ans;
    return 0;
}