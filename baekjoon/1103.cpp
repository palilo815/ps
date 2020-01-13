#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool Inf, visited[50][50];
char Board[50][50];
int row, col, Cache[50][50], mov_y[4] = { -1,1,0,0 }, mov_x[4] = { 0,0,-1,1 };

int DP(int r, int c)
{
    if (visited[r][c]) Inf = true;
    else visited[r][c] = true;
    if (Inf) return 0;
    int& ret = Cache[r][c];
    if (ret != -1) return ret;

    ret = 0;
    int J = Board[r][c] - '0';
    loop(i, 4) {
        int R = mov_y[i] * J + r, C = mov_x[i] * J + c;
        if (R < 0 || R >= row || C < 0 || C >= col) ret = max(ret, 1);
        else if (Board[R][C] == 'H') ret = max(ret, 1);
        else {
            ret = max(ret, DP(R, C) + 1);
            visited[R][C] = false;
        }
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(Cache, -1, sizeof(Cache));
    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> Board[i][j];
    int Ans = 0;
    Ans = DP(0, 0);
    if (Inf) cout << -1;
    else cout << Ans;
    return 0;
}