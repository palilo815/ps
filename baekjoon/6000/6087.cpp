#include <bits/stdc++.h>
using namespace std;

const int mx = 100;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mx + 2][mx + 2];
int dist[mx + 2][mx + 2];

void bfs(int sr, int sc) {
    mat[sr][sc] = '*';

    memset(dist, 0x3f, sizeof(dist));
    dist[sr][sc] = -1;

    queue<pair<int, int>> q;
    q.emplace(sr, sc);

    for (;;) {
        auto [r, c] = q.front(); q.pop();
        if (mat[r][c] == 'C') {cout << dist[r][c]; return;}

        for (int i = 0; i < 4; ++i)
            for (int R = r + mov[i][0], C = c + mov[i][1]; mat[R][C] ^ '*' && dist[R][C] >= dist[r][c] + 1; R += mov[i][0], C += mov[i][1])
                if (dist[R][C] > dist[r][c] + 1) {
                    dist[R][C] = dist[r][c] + 1;
                    q.emplace(R, C);
                }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    memset(mat, '*', sizeof(mat));

    int col, row; cin >> col >> row;
    for (int i = 1; i <= row; ++i)
        cin >> (mat[i] + 1);

    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            if (mat[i][j] == 'C') {
                bfs(i, j);
                return 0;
            }
}