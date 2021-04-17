#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    string s;
    cin >> n >> m >> k >> s;

    vector<vector<int>> cost(m, vector<int>(m));
    for (auto& vt : cost)
        for (auto& x : vt)
            cin >> x;

    for (int k = 0; k < m; ++k)
        for (int u = 0; u < m; ++u)
            for (int v = 0; v < m; ++v)
                cost[u][v] = min(cost[u][v], cost[u][k] + cost[k][v]);

    array<int, 26> sum {};
    for (int i = 0; i < k; ++i)
        for (int alpha = 0; alpha < m; ++alpha)
            sum[alpha] += cost[s[i] - 'a'][alpha];

    vector<array<int, 26>> dp(n);
    dp[k - 1] = sum;

    for (int i = k; i < n; ++i) {
        for (int alpha = 0; alpha < m; ++alpha) sum[alpha] -= cost[s[i - k] - 'a'][alpha];
        for (int alpha = 0; alpha < m; ++alpha) sum[alpha] += cost[s[i] - 'a'][alpha];

        const int c = i - k < k - 1 ? 0x3f3f3f3f : *min_element(dp[i - k].begin(), dp[i - k].begin() + m);
        for (int alpha = 0; alpha < m; ++alpha)
            dp[i][alpha] = min(dp[i - 1][alpha] + cost[s[i] - 'a'][alpha], c + sum[alpha]);
    }
    cout << *min_element(dp.back().begin(), dp.back().begin() + m);
}