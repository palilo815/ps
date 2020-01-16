#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int row, col, Map[100][100];
int mov[4][2] = { -1,0,1,0,0,-1,0,1 };
void DFS(int r, int c)
{
    Map[r][c] = -1;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col) continue;
        if (Map[R][C] == 0)
            DFS(R, C);
    }
}
bool melt(int r, int c)
{
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (Map[R][C] == -1) return true;
    }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int cheese = 0;
    cin >> row >> col;
    loop(i, row) loop(j, col) {
        cin >> Map[i][j];
        if (Map[i][j]) ++cheese;
    }
    DFS(0, 0);
    // Map 설명
    // 1 : 치즈,  0 : 공기,  -1 : "외부" 공기
    // 2 : 방금 전에 녹은 치즈

    int ans = 0, prev = 0;
    while (cheese) {
        loop(i, row) loop(j, col)
            if (Map[i][j] == 1 && melt(i, j))
                Map[i][j] = 2;
        prev = cheese;
        loop(i, row) loop(j, col)
            if (Map[i][j] == 2) {
                DFS(i, j);
                --cheese;
            }
        ++ans;
    }
    cout << ans << '\n' << prev;
    return 0;
}