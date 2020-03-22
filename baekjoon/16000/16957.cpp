#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int MAX = 500;
const int mov[8][2] = { -1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1 };

int row, col;
int board[MAX][MAX];
p DP[MAX][MAX];

p DFS(int r, int c) {
    p& ret = DP[r][c];
    if (ret.first != -1) return ret;

    int vr = -1, vc = -1;
    loop(i, 8) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C<0 || C >= col || board[R][C] > board[r][c]) continue;
        if (vr == -1 || board[vr][vc] > board[R][C])
            vr = R, vc = C;
    }
    if (vr == -1) return ret = { r,c };
    else return ret = DFS(vr, vc);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> board[i][j];
    
    memset(DP, -1, sizeof(DP));
    loop(i, row) loop(j, col) DFS(i, j);

    memset(board, 0, sizeof(board));
    loop(i, row) loop(j, col) {
        auto [r, c] = DP[i][j];
        ++board[r][c];
    }

    loop(i, row) {
        loop(j, col) cout << board[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}