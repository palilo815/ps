#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int img[40][40];
int filter(int r, int c, int T)
{
    int n = 0;
    loop(i, 3) loop(j, 3)
        if (img[r + i][c + j] < T)
            ++n;
    // n < 5라면 중앙값이 무조건 T보다 크다.
    return n < 5;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, T, ans = 0;
    cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> img[i][j];
    cin >> T;
    loop(r, row - 2) loop(c, col - 2)
        ans += filter(r, c, T);
    cout << ans;
    return 0;
}