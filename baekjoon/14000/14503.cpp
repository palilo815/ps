#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 50;

int M[max_N][max_N], row, col;
int mov[4][2] = { -1,0,0,1,1,0,0,-1 };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int r, c, d, ans = 0;
    cin >> row >> col >> r >> c >> d;
    loop(i, row) loop(j, col)
        cin >> M[i][j];

    while (1) {
    p1:
        // 청소 완료한 칸은 2로 채운다.
        M[r][c] = 2; ++ans;
    p2:
        loop(i, 4) {
            // 왼쪽으로 돈다.
            --d;
            if (d < 0) d = 3;
            int R = r + mov[d][0], C = c + mov[d][1];
            // 해당 방향이 끝이거나, 벽이거나, 이미 청솨 됐다면 pass
            if (R < 0 || R >= row || C < 0 || C >= col || M[R][C]) continue;
            r = R, c = C;
            goto p1;
        }
        // B : back
        int B = (d + 2) % 4;
        int R = r + mov[B][0], C = c + mov[B][1];
        // 뒤가 끝이거나 벽이면 종료
        if (R < 0 || R >= row || C < 0 || C >= col || M[R][C] == 1) break;
        r = R, c = C;
        goto p2;
    }
    cout << ans;
    return 0;
}