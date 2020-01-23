#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
bool made[1000000];
int mat[5][5];
void DFS(int r, int c, int num, int cnt)
{
    if (cnt == 5) {
        made[num] = true;
        return;
    }
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R == -1 || R == 5 || C == -1 || C == 5) continue;
        DFS(R, C, num * 10 + mat[R][C], cnt + 1);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 5) loop(j, 5)
        cin >> mat[i][j];
    loop(i, 5) loop(j, 5)
        DFS(i, j, mat[i][j], 0);

    int ans = 0;
    loop(i, 1000000)
        if (made[i]) ++ans;
    cout << ans;
    return 0;
}