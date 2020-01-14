#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int DP[1000][1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col;
    cin >> row >> col;
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        DP[i][j] = c - '0';
    }
    int ans = 0;
    loop(i, row)
        if (DP[i][0]) {
            ans = 1;
            break;
        }
    if (ans == 0) loop(i, col)
        if (DP[0][i]) {
            ans = 1;
            break;
        }


    // DP[i][j] : (i,j) 에서 만들 수 있는 최대 정사각형의 변의 길이
    for (int i = 1; i < row; ++i)
        for (int j = 1; j < col; ++j)
            if (DP[i][j]) {
                // DP[i-1][j-1]에서 만들 수 있는 변은 prevL,
                // i행과 j열이 전부 1이더라도 DP[i][j]는 prev_L+1이 최대다.
                int prevL = DP[i - 1][j - 1], y, x;

                // (i,j)에서 0이 나올 때까지 위로 올라간다.
                for (y = 1; y <= prevL; ++y)
                    if (DP[i - y][j] == 0) break;
                // (i,j)에서 0이 나올 때까지 왼쪽으로 간다.
                for (x = 1; x <= prevL; ++x)
                    if (DP[i][j - x] == 0) break;
                DP[i][j] = min(x, y);
                ans = max(DP[i][j], ans);
            }
    cout << ans * ans;
    return 0;
}