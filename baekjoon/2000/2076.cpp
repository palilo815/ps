#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<pair<int, int>> vec(n);
    for (auto& [x, y] : vec)
        cin >> x >> y;

    sort(vec.begin(), vec.end(), [&](auto& a, auto& b) {
        return atan2(a.second, a.first) < atan2(b.second, b.first);
    });

    auto sum_vec = [&](int x, int y) {
        return int64_t(x) * x + int64_t(y) * y;
    };
    auto ccw = [&](pair<int, int>& a, pair<int, int>& c) {
        auto ret = int64_t(-a.first) * (c.second - a.second) -
                   int64_t(-a.second) * (c.first - a.first);
        return ret ? (ret > 0 ? 1 : -1) : 0;
    };

    int x = vec[0].first, y = vec[0].second;
    int64_t ans = sum_vec(x, y);
    if (n == 1) return cout << ans, 0;

    for (int i = 0, j = 1; i < n; ++i) {
        ans = max(ans, sum_vec(x, y));
        while (i != j && ccw(vec[i], vec[j]) != 1) {
            x += vec[j].first, y += vec[j].second;
            j = j == n - 1 ? 0 : j + 1;
            ans = max(ans, sum_vec(x, y));
        }
        x -= vec[i].first, y -= vec[i].second;
    }
    cout << ans;
}