#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=1;i<=n;++i)
int board[15][15];

// (sY,sX) -> (eY,eX) 로 가는 경로의 수 return
int DP(int sY, int sX, int eY, int eX)
{
    board[sY][sX] = 1;
    for (int i = sY + 1; i <= eY; ++i)
        board[i][sX] = 1;
    for (int i = sX + 1; i <= eX; ++i)
        board[sY][i] = 1;
    for (int i = sY + 1; i <= eY; ++i)
        for (int j = sX + 1; j <= eX; ++j)
            board[i][j] = board[i - 1][j] + board[i][j - 1];
    return board[eY][eX];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, M;
    cin >> row >> col >> M;
    // if 표시가 없으면 그냥 (0,0)->(row-1,col-1) 가짓수
    if (M == 0)
        cout << DP(0, 0, row - 1, col - 1);
    // 표시가 있으면 (0,0)->표시 경우의 수 * 표시->(row-1,col-1) 경우의 수
    else {
        int mY = (M - 1) / col, mX = (M - 1) % col;
        int ans1 = DP(0, 0, mY, mX), ans2 = DP(mY, mX, row - 1, col - 1);
        cout << ans1 * ans2;
    }
    return 0;
}