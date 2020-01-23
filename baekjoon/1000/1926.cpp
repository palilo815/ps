#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool paint[500][500];
int row, col, mov[4][2] = { -1,0,1,0,0,-1,0,1 };
int DFS(int r, int c)
{
    int ret = 1;
    paint[r][c] = false;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || !paint[R][C]) continue;
        ret += DFS(R, C);
    }
    return ret;
}
int main()
{
    cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> paint[i][j];

    int cnt = 0, area = 0;
    loop(i, row) loop(j, col)
        if (paint[i][j]) {
            area = max(area, DFS(i, j));
            ++cnt;
        }
    cout << cnt << '\n' << area;
    return 0;
}