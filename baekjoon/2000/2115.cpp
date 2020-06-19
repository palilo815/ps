#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 1000;

char mat[M][M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> mat[i][j];

    int ans = 0;
    loop(i, row - 1) {
        int c1 = 0, c2 = 0;
        loop(j, col) {
            if (mat[i][j] == 'X' && mat[i + 1][j] == '.') {
                if (++c1 == 2) c1 = 0, ++ans;
            }
            else c1 = 0;
            if (mat[i][j] == '.' && mat[i + 1][j] == 'X') {
                if (++c2 == 2) c2 = 0, ++ans;
            }
            else c2 = 0;
        }
    }
    loop(j, col - 1) {
        int c1 = 0, c2 = 0;
        loop(i, row) {
            if (mat[i][j] == 'X' && mat[i][j + 1] == '.') {
                if (++c1 == 2) c1 = 0, ++ans;
            }
            else c1 = 0;
            if (mat[i][j] == '.' && mat[i][j + 1] == 'X') {
                if (++c2 == 2) c2 = 0, ++ans;
            }
            else c2 = 0;
        }
    }
    cout << ans;
    return 0;
}