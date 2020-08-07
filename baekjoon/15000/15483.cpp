#include <bits/stdc++.h>
using namespace std;

const int mx = 1001;

char a[mx], b[mx];
int dp[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> a >> b;
    int N = strlen(b);

    iota(dp + 1, dp + N + 1, 1);
    for (int i = 0; a[i]; ++i) {
        int pre = dp[0];
        dp[0] = i + 1;

        for (int j = 0; b[j]; ++j) {
            int cur = dp[j + 1];
            dp[j + 1] = a[i] == b[j] ? pre : pre = min({pre, dp[j], dp[j + 1]}) + 1;
            pre = cur;
        }
    }
    cout << dp[N];
    return 0;
}