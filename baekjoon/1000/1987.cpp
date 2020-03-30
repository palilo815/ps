#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

char board[20][20];
int row, col, ans;

void DFS(int y, int x, int select) {
    ans = max(ans, __builtin_popcount(select));
    loop(i, 4) {
        int Y = y + mov[i][0], X = x + mov[i][1];
        if (Y < 0 || Y >= row || X < 0 || X >= col) continue;

        int v = 1 << (board[Y][X] - 'A');
        if (!(select & v))
            DFS(Y, X, select | v);
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> board[i][j];

    DFS(0, 0, 1 << (board[0][0] - 'A'));
    cout << ans;
    return 0;
}