#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 10;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mx][mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    loop(i, 10) loop(j, 10) cin >> mat[i][j];

    queue<pair<int, int>> q;
    loop(i, 10) loop(j, 10) if (mat[i][j] == 'L') {
        q.emplace(i, j);
        mat[i][j] = 'R';
    }
    q.emplace(-1, -1);

    int ans = 0;
    for (;;) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {++ans; q.emplace(r, c); continue;}

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R ^ 10 && ~C && C ^ 10 && mat[R][C]^'R') {
                if (mat[R][C] == 'B') {cout << ans; return 0;}
                else {
                    mat[R][C] = 'R';
                    q.emplace(R, C);
                }
            }
        }
    }
    return 0;
}