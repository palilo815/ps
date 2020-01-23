#include<iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int row, col, mov[8][2] = { -1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1 };
bool land[50][50];
void DFS(int r, int c)
{
    land[r][c] = false;
    loop(i, 8) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || !land[R][C]) continue;
        DFS(R, C);
    }
}
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    while (1) {
        cin >> col >> row;
        if (row == 0) break;
        loop(i, row) loop(j, col) cin >> land[i][j];
        int ans = 0;
        loop(i,row) loop(j,col)
            if (land[i][j]) {
                ++ans;
                DFS(i, j);
            }
        cout << ans << '\n';
    }
    return 0;
}