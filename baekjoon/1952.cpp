#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool visited[100][100];
int mov[4][2] = { -1,0,0,1,1,0,0,-1 };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, r = 0, c = 0, D = 0, ans = -1;
    cin >> row >> col;
    while (1) {
        // 이동
        visited[r][c] = true;
        int R = r + mov[D][0], C = c + mov[D][1];

        // 만약 이동한 칸이 범위 밖이면
        if (R == -1 || R == row || C == -1 || C == col || visited[R][C]) {
            // 방향을 바꾸고 다시 이동
            D = (D + 1) % 4;
            R = r + mov[D][0], C = c + mov[D][1];
            // 만약 방향을 바꿔도 안되면 끝
            if (R == -1 || R == row || C == -1 || C == col || visited[R][C]) break;
            ++ans;
        }
        r = R, c = C;
    }
    cout << ans;
    return 0;
}