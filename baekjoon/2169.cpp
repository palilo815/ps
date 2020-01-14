#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int row, col, MARS[1000][1000], DP[2][1000][1000];
// D==0 : 오른쪽, D==1 : 왼쪽에서 왔음.
int TopDown(int D, int r, int c)
{
    if (r == 0) return DP[0][r][c];
    int& ret = DP[D][r][c];
    if (ret != INT32_MIN) return ret;

    // 윗 칸에서 내려온 경우
    ret = max(TopDown(0, r - 1, c), TopDown(1, r - 1, c));

    // 가로로 이동할 때는 D를 유지한 채로 이동했어야 한다.
    if (D == 1 && c != col - 1)
        ret = max(ret, TopDown(1, r, c + 1));
    else if (D == 0 && c != 0)
        ret = max(ret, TopDown(0, r, c - 1));
    ret += MARS[r][c];
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> MARS[i][j];
    DP[0][0][0] = MARS[0][0];
    for (int j = 1; j < col; ++j)
        DP[0][0][j] = DP[0][0][j - 1] + MARS[0][j];
    loop(k, 2) for (int i = 1; i < row; ++i) loop(j, col)
            DP[k][i][j] = INT32_MIN;
    cout << max(TopDown(0, row - 1, col - 1), TopDown(1, row - 1, col - 1));
    return 0;
}