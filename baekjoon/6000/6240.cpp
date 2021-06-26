#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m;
    string s;
    cin >> n >> m >> s;

    array<int, 26> cost;
    for (int i = 0, c0, c1; i < n; ++i) {
        char alp;
        cin >> alp >> c0 >> c1;
        cost[alp - 'a'] = min(c0, c1);
    }

    // dp[i][j] = minimum cost to change s[i, j) to palindrome
    vector dp(m, vector<int>(m + 1, -1));
    for (int i = 0; i < m; ++i)
        dp[i][i] = dp[i][i + 1] = 0;

    for (int len = 1; len < m; ++len)
        for (int i = 0; i + len < m; ++i) {
            if (s[i] == s[i + len])
                dp[i][i + len + 1] = dp[i + 1][i + len];
            else
                dp[i][i + len + 1] = min(dp[i][i + len] + cost[s[i + len] - 'a'], dp[i + 1][i + len + 1] + cost[s[i] - 'a']);
        }
    cout << dp[0][m];
}