#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> a(k);
    for (auto& [x, y] : a) {
        cin >> x >> y;
    }
    sort(a.begin(), a.end());
    vector<int> dp;
    for (const auto& [_, y] : a) {
        const auto it = lower_bound(dp.begin(), dp.end(), y, greater());
        if (it == dp.end()) {
            dp.emplace_back(y);
        } else {
            *it = y;
        }
    }
    cout << dp.size();
}