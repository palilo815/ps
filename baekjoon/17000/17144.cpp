#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int MAX = 50;

int row, col;
int dust[MAX][MAX];
int tmp[MAX][MAX];

void spread() {
    memset(tmp, 0, sizeof(tmp));
    loop(r, row) loop(c, col) if (dust[r][c] > 0) {
        int cnt = 0;
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || dust[R][C] == -1) continue;
            ++cnt;
            tmp[R][C] += dust[r][c] / 5;
        }
        dust[r][c] -= dust[r][c] / 5 * cnt;
    }
    loop(r, row) loop(c, col) dust[r][c] += tmp[r][c];
}
void machine(int U, int D) {
    for (int r = U - 1; r > 0; --r)
        dust[r][0] = dust[r - 1][0];
    for (int r = D + 1; r < row - 1; ++r)
        dust[r][0] = dust[r + 1][0];
    
    loop(c, col - 1) {
        dust[0][c] = dust[0][c + 1];
        dust[row - 1][c] = dust[row - 1][c + 1];
    }
    
    loop(r, U)
        dust[r][col - 1] = dust[r + 1][col - 1];
    for (int r = row - 1; r > D; --r)
        dust[r][col - 1] = dust[r - 1][col - 1];

    for (int c = col - 1; c > 1; --c) {
        dust[U][c] = dust[U][c - 1];
        dust[D][c] = dust[D][c - 1];
    }
    dust[U][1] = dust[D][1] = 0;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> row >> col >> T;
    int U = -1, D = -1;
    loop(i, row) loop(j, col) {
        cin >> dust[i][j];
        if (dust[i][j] == -1) {
            if (U == -1) U = i;
            else D = i;
        }
    }

    while (T--) {
        spread();
        machine(U, D);
    }

    int ans = 0;
    loop(i, row) loop(j, col) ans += dust[i][j];
    cout << ans + 2;
    return 0;
}