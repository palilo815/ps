#include <bits/stdc++.h>
using namespace std;

const int mx = 1e3;

int mat[mx + 2][mx + 2];
queue<pair<int, int>> q;

void bfs(int sr, int sc) {
    q.emplace(sr, sc);
    mat[sr][sc] = 0;

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int R = r - 1; R <= r + 1; ++R)
            for (int C = c - 1; C <= c + 1; ++C)
                if (mat[R][C]) {
                    mat[R][C] = 0;
                    q.emplace(R, C);
                }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            cin >> mat[i][j];

    int ans = 0;
    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            if (mat[i][j]) {
                ++ans;
                bfs(i, j);
            }
    cout << ans;
    return 0;
}