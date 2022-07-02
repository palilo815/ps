#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> to(n);
    for (int i = 0; i < n; ++i) {
        int delta = 0;
        for (int j = i + 1; j; j /= 10) {
            delta += j % 10;
        }
        to[i] = (i + delta) % n;
    }
    vector<int> indeg(n);
    for (const auto& x : to) {
        ++indeg[x];
    }
    vector<int> stk;
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) {
            stk.emplace_back(i);
        }
    }
    vector<int> dp(n);
    while (!stk.empty()) {
        const auto u = stk.back();
        stk.pop_back();
        dp[to[u]] = max(dp[to[u]], dp[u] + 1);
        if (--indeg[to[u]] == 0) {
            stk.emplace_back(to[u]);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) continue;
        int cycle = 1;
        int mx = dp[i];
        for (int j = to[i]; j != i; j = to[j], ++cycle) {
            mx = max(mx, dp[j]);
            indeg[j] = 0;
        }
        ans = max(ans, mx + cycle);
    }
    cout << ans;
}
