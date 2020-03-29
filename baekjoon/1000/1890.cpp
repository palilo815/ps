#include<iostream>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

ll board[100][100], DP[100][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) loop(j, n)
        cin >> board[i][j];
    DP[0][0] = 1;
    loop(i, n) loop(j, n) {
        ll d = board[i][j];
        if (d == 0) continue;

        if (i + d < n) DP[i + d][j] += DP[i][j];
        if (j + d < n) DP[i][j + d] += DP[i][j];
    }
    cout << DP[n - 1][n - 1];
    return 0;
}