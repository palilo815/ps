#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int mov[4][2] = { 0,-1,-1,0,1,0,0,1 }; // 왼 위 아래 오
int lake[2][100][100];

int fishing(int T, int row, int c)
{
    loop(i, row)
        if (lake[T][i][c]) {
            int ret = lake[T][i][c] / 4096;
            lake[T][i][c] = 0;
            return ret;
        }
    return 0;
}
void moving(int T, int row, int col)
{
    memset(lake[1 - T], 0, sizeof(lake[1 - T]));
    loop(r, row) loop(c, col)
        if (lake[T][r][c]) {
            int Size = lake[T][r][c];
            int V = Size % 4096; Size /= 4096;
            int D = V % 4; V /= 4;

            int R = r + mov[D][0] * V, C = c + mov[D][1] * V;
            while (R > row - 1 || R < 0) {
                if (R > row - 1) R = 2 * (row - 1) - R;
                else R = -R;
                D = 3 - D;
            }
            while (C > col - 1 || C < 0) {
                if (C > col - 1) C = 2 * (col - 1) - C;
                else C = -C;
                D = 3 - D;
            }
            lake[1 - T][R][C] = max(lake[1 - T][R][C], Size * 4096 + V * 4 + D);
        }
}
int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, N; cin >> row >> col >> N;
    while (N--) {
        int r, c, V, D, Size;
        cin >> r >> c >> V >> D >> Size;
        lake[0][r - 1][c - 1] = Size * 4096 + V * 4 + (D % 4);
    }

    int ans = 0;
    loop(pos, col) {
        // pos위치에서 낚는다.
        ans += fishing(pos % 2, row, pos);
        // 상어 이동
        moving(pos % 2, row, col);
    }
    cout << ans;
    return 0;
}