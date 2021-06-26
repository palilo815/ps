#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> cow(n), grass(m);
    for (auto& [x, y] : cow) cin >> x >> y;
    for (auto& [x, y] : grass) cin >> x >> y;

    sort(cow.begin(), cow.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.second > rhs.second;
    });
    sort(grass.begin(), grass.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.second > rhs.second;
    });

    multiset<int> prices;
    int64_t ans = 0;

    int ptr = 0;
    for (const auto& [x, y] : cow) {
        while (ptr < m && grass[ptr].second >= y)
            prices.emplace(grass[ptr++].first);
        if (auto it = prices.lower_bound(x); it == prices.end())
            return cout << -1, 0;
        else {
            ans += *it;
            prices.erase(it);
        }
    }
    cout << ans;
}