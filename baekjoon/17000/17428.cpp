#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t k;
    cin >> n >> k;
    // dp[i][j].first  = ')'가 j개 더 많고 i번째 괄호가 '('인 괄호 문자열 [i, n) 개수
    // dp[i][j].second = ')'가 j개 더 많고 i번째 괄호가 ')'인 괄호 문자열 [i, n) 개수
    vector dp(n, vector<pair<int64_t, int64_t>>(n + 1));
    dp[n - 1][1].second = 1;
    for (int i = n - 1; i--;) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j - 1].first += dp[i + 1][j].first + dp[i + 1][j].second;
        }
        for (int j = 0; j < n; ++j) {
            dp[i][j + 1].second += dp[i + 1][j].first + dp[i + 1][j].second;
        }
    }
    if (dp[0][0].first <= k) return cout << -1, 0;
    for (int i = 0, j = 0; i < n; ++i) {
        if (dp[i][j].first > k) {
            cout << '(';
            ++j;
        } else {
            cout << ')';
            k -= dp[i][j].first;
            --j;
        }
    }
}