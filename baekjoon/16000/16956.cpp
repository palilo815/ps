#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 500;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mx][mx + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    loop(i, row) cin >> mat[i];

    loop(r, row) loop(c, col) if (mat[r][c] == 'W') {
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R == -1 || R == row || C == -1 || C == col) continue;
            if (mat[R][C] == '.') mat[R][C] = 'D';
            else if (mat[R][C] == 'S') {cout << 0; return 0;}
        }
    }

    cout << "1\n";
    loop(i, row) cout << mat[i] << '\n';
    return 0;
}