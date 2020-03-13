#include <algorithm>
#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 50;

char board[MAX][MAX];
char tmp[8][8];

int solve(int r, int c) {
    int W = 0, B = 0;
    loop(i, 8) loop(j, 8)
        board[r + i][c + j] == tmp[i][j] ? ++B : ++W;
    return min(W, B);
}

int main() {
    loop(i, 8) loop(j, 8) {
        if ((i + j) % 2) tmp[i][j] = 'B';
        else tmp[i][j] = 'W';
    }
    
    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> board[i][j];

    int ans = 64;
    loop(i, row - 7) loop(j, col - 7)
        ans = min(ans, solve(i, j));
    cout << ans;
    return 0;
}