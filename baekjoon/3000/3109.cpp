#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_R = 10000;
const int max_C = 500;
const int mov[3][2] = { -1, 1, 0, 1, 1, 1 };

int row, col;
bool wall[max_R][max_C];

int conn(int r, int c) {
    wall[r][c] = true;
    loop(i, 3) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || wall[R][C]) continue;
        if (C == col - 1 || conn(R, C)) return 1;
    }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> row >> col;
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        if (c == 'x') wall[i][j] = true;
    }

    int ans = 0;
    loop(i, row) if (!wall[i][0])
        ans += conn(i, 0);
    cout << ans;
    return 0;
}