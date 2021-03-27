#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    array<vector<int>, 101> com;
    // com[100] is sentinel

    int n;
    cin >> n;

    vector<int> t(n);
    for (int i = 0, c; i < n; ++i) {
        cin >> c >> t[i], --c;
        com[c].emplace_back(i);
    }

    vector<int> dp(n);
    for (int i = 0; i < 100; ++i) {
        if (com[i].empty()) break;
        for (const auto& u : com[i]) {
            dp[u] += t[u];
            for (const auto& v : com[i + 1])
                dp[v] = max(dp[v], dp[u] + (u - v) * (u - v));
        }
    }
    cout << *max_element(dp.begin(), dp.end());
}