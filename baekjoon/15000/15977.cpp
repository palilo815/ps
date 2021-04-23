#include <bits/stdc++.h>
using namespace std;

void solve2() {
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (auto& [x, _] : a) cin >> x;
    for (auto& [_, y] : a) cin >> y;

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    vector<int> dp;
    for (const auto& [_, y] : a)
        if (auto it = lower_bound(dp.begin(), dp.end(), y); it == dp.end())
            dp.emplace_back(y);
        else
            *it = y;
    cout << dp.size();
}
void solve3() {
    int n;
    cin >> n;

    vector<tuple<int, int, int>> a(n);
    for (auto& [x, y, z] : a) cin >> x;
    for (auto& [x, y, z] : a) cin >> y;
    for (auto& [x, y, z] : a) cin >> z;

    sort(a.begin(), a.end(), [](auto& a, auto& b) {
        return get<0>(a) < get<0>(b);
    });

    vector<set<pair<int, int>>> dp;
    auto ok = [&](int set_id, pair<int, int> point) {
        auto it = dp[set_id].lower_bound(point);
        return it == dp[set_id].begin() || prev(it)->second > point.second;
    };

    for (const auto& [_, y, z] : a) {
        int lo = 0, hi = dp.size();
        while (lo != hi) {
            int mid = (lo + hi) >> 1;
            ok(mid, make_pair(y, z)) ? hi = mid : lo = mid + 1;
        }

        if (lo == int(dp.size()))
            dp.emplace_back(set<pair<int, int>> {{y, z}});
        else
            for (auto it = next(dp[lo].emplace(y, z).first); it != dp[lo].end(); it = dp[lo].erase(it))
                if (it->second < z)
                    break;
    }
    cout << dp.size();
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int m;
    cin >> m;
    m == 2 ? solve2() : solve3();
}