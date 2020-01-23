#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool Map[100][100];
int row, col, mov[4][2] = { -1,0,1,0,0,-1,0,1 };
int DFS(int r, int c)
{
    int ret = 1;
    Map[r][c] = false;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col) continue;
        if (Map[R][C])
            ret += DFS(R, C);
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int k; cin >> row >> col >> k;
    while (k--) {
        int r, c; cin >> r >> c;
        Map[r - 1][c - 1] = true;
    }
    int ans = 0;
    loop(i, row) loop(j, col)
        if (Map[i][j])
            ans = max(ans, DFS(i, j));
    cout << ans;
    return 0;
}