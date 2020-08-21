#include <bits/stdc++.h>
using namespace std;

const int mx = 50;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mx + 2][mx + 2];
int t, sz[10];
pair<int, int> idx[10];

int dfs(int r, int c) {
    mat[r][c] = t;
    int ret = 1;
    for (int i = 0; i < 4; ++i) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (mat[R][C] == '1')
            ret += dfs(R, C);
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    for (int i = 1; i <= row; ++i)
        cin >> (mat[i] + 1);

    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            if (mat[i][j] == '1') {
                int cnt = dfs(i, j);
                sz[t++] = cnt;
            }

    for (int i = 0; i < t; ++i)
        idx[i] = {sz[i], i};
    sort(idx, idx + t);
    for (int i = 0; i < t; ++i)
        sz[idx[i].second] = i + 1;

    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j)
            cout << (mat[i][j] == '0' ? 0 : sz[mat[i][j]]);
        cout << '\n';
    }
    return 0;
}