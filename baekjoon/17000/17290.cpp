#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char board[10][10];
int main()
{
    int r, c; cin >> r >> c;
    --r, --c;
    loop(i, 10) loop(j, 10) cin >> board[i][j];
    loop(i, 10) loop(j, 10)
        if (board[i][j] == 'o')
            loop(k, 10) {
            if (board[i][k] == 'x') board[i][k] = 0;
            if (board[k][j] == 'x') board[k][j] = 0;
        }

    int ans = INT_MAX;
    loop(i, 10) loop(j, 10)
        if (board[i][j] == 'x')
            ans = min(ans, abs(i - r) + abs(j - c));
    cout << ans;
    return 0;
}