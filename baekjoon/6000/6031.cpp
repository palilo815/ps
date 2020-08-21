#include <bits/stdc++.h>
using namespace std;

const int mx = 750;

char mat[mx + 2][mx + 2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> col >> row;
    for (int i = 1 ; i <= row; ++i)
        cin >> (mat[i] + 1);

    function<int(int, int)> dfs = [&](int r, int c) {
        int ret = 1;
        mat[r][c] = 0;
        for (int R = r - 1; R <= r + 1; ++R)
            for (int C = c - 1; C <= c + 1; ++C)
                if (mat[R][C] == '.')
                    ret += dfs(R, C);
        return ret;
    };

    int ans = 0;
    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            if (mat[i][j] == '.')
                ans = max(ans, dfs(i, j));
    cout << ans;
    return 0;
}