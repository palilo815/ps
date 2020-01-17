#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char board[30][30];
int mov[4][2] = { 0,1,1,0,1,1,1,-1 };
int N;

bool win(int r, int c, char name)
{
    loop(i, 4) {
        int R1 = r + mov[i][0], C1 = c + mov[i][1];
        int R2 = R1 + mov[i][0], C2 = C1 + mov[i][1];
        if (R2 < 0 || R2 >= N || C2 < 0 || C2 >= N) continue;
        if (name == board[R1][C1] && board[R1][C1] == board[R2][C2]) return true;
    }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) loop(j, N) cin >> board[i][j];

    char winner = 0;
    loop(i, N) loop(j, N)
        if (board[i][j] != '.' && win(i, j, board[i][j])) {
            winner = board[i][j];
            goto OUT;
        }
OUT:;
    if (winner) cout << winner;
    else cout << "ongoing";
    return 0;
}