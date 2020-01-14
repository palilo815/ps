#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char board[1000][1000];
int row, col;
int mov_Q[8][2] = { -1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1 }, mov_K[8][2] = { -1,-2, -2,-1, -2,1, -1,2, 1,2, 2,1, 2,-1, 1,-2 };
void place(char P)
{
    int n; cin >> n;
    while (n--) {
        int r, c; cin >> r >> c;
        board[r - 1][c - 1] = P;
    }
}

// 위험한 칸을 전부 'X'로 표시한다.
void check(int r, int c, char P)
{
    switch (P) {
    case 'Q':
        loop(i, 8) {
            int R = r, C = c, dR = mov_Q[i][0], dC = mov_Q[i][1];
            while (1) {
                R += dR, C += dC;
                if (R < 0 || R >= row || C < 0 || C >= col || (board[R][C] && board[R][C] != 'X')) break;
                board[R][C] = 'X';
            }
        }
        break;
    case 'K':
        loop(i, 8) {
            int R = r + mov_K[i][0], C = c + mov_K[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || board[R][C]) continue;
            board[R][C] = 'X';
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    // Queen King Pawn을 놓는다.
    place('Q'), place('K'), place('P');

    // Queen, King의 이동 범위에 있는 칸을 'X'로 표시한다.
    loop(i, row) loop(j, col) {
        char P = board[i][j];
        if (P == 'Q' || P == 'K')
            check(i, j, P);
    }

    // 표시가 안된 칸은 안전하다.
    int ans = 0;
    loop(i, row) loop(j, col)
        if (!board[i][j]) ++ans;
    cout << ans;
    return 0;
}