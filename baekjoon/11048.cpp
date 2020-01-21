#include <iostream>
#include <algorithm>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

int candy[1001][1001], DP[1001][1001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** initialize ** 
    int row, col; cin >> row >> col;
    LOOP(i, row) LOOP(j, col) cin >> candy[i][j];

    // ** dynamic programming **
    LOOP(i, row) LOOP(j, col) {
        int tmp = max(DP[i - 1][j], DP[i][j - 1]);
        tmp = max(tmp, DP[i - 1][j - 1]);
        DP[i][j] = tmp + candy[i][j];
    }
    cout << DP[row][col];
}