#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 50;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mx][mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> mat[i][j];

    queue<pair<int, int>> q;

    function<void(int, int)> dfs = [&](int r, int c) {
        q.emplace(r, c);
        mat[r][c] = 'Y';
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R ^ row && ~C && C ^ col && mat[R][C] == 'X')
                dfs(R, C);
        }
    };
    loop(i, row) loop(j, col) if (mat[i][j] == 'X') {
        dfs(i, j);
        goto out;
    }
out:;
    q.emplace(-1, -1);
    int ans = 0;
    for (;;) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {++ans; q.emplace(r, c); continue;}

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R ^ row && ~C && C ^ col && mat[R][C] ^ 'Y') {
                if (mat[R][C] == '.') mat[R][C] = 'Y', q.emplace(R, C);
                else {cout << ans; return 0;}
            }
        }
    }
}