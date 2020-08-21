#include <bits/stdc++.h>
using namespace std;

const int mx = 100;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mx + 2][mx + 2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    for (int i = 1; i <= row; ++i)
        cin >> (mat[i] + 1);

    queue<pair<int, int>> q;
    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            if (mat[i][j] == 'B') {
                mat[i][j] = 0;
                q.emplace(i, j);
            }

    q.emplace(0, 0);
    int ans = 1;
    for (;;) {
        auto [r, c] = q.front(); q.pop();
        if (!r) {++ans; q.emplace(0, 0); continue;}

        for (int i = 0; i < 4; ++i) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (mat[R][C] == '.') {
                mat[R][C] = 0;
                q.emplace(R, C);
            }
            else if (mat[R][C] == 'C') {cout << ans; return 0;}
        }
    }
}