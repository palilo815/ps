#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    vector<int> indegree(n);
    for (auto& [x, y] : a) {
        cin >> x >> y, --x;
        ++indegree[x];
    }
    int64_t ans {};
    for (int i {}; i < n; ++i) {
        if (indegree[i]) continue;
        for (auto j {i};; j = a[j].first) {
            indegree[j] = -1;
            ans += a[j].second;
            if (--indegree[a[j].first]) break;
        }
    }
    for (int i {}; i < n; ++i) {
        if (indegree[i] <= 0) continue;
        ans += a[i].second;
        auto mn {a[i].second};
        for (auto j {a[i].first}; i != j; j = a[j].first) {
            indegree[j] = 0;
            ans += a[j].second;
            mn = min(mn, a[j].second);
        }
        ans -= mn;
    }
    cout << ans;
}
