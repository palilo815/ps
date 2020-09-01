#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int dp[2][17][17];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int a, d;
    int (*prv)[17] = dp[0], (*cur)[17] = dp[1];
    prv[0][0] = 1;

    for (int a, d; cin >> a >> d; swap(prv, cur)) {
        loop(i, 16) loop(j, 16) if (prv[i][j]) {
            cur[i][j] = max(cur[i][j], prv[i][j]);
            cur[i][j + 1] = max(cur[i][j + 1], prv[i][j] + a);
            cur[i + 1][j] = max(cur[i + 1][j], prv[i][j] + d);
        }
    }
    cout << prv[15][15] - 1;
    return 0;
}