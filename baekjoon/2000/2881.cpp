#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<pair<int, int>> sorted_by_xy(n);
    for (auto& [x, y] : sorted_by_xy) {
        cin >> x >> y;
    }
    auto sorted_by_yx(sorted_by_xy);
    auto cmp_yx = [&](const auto& lhs, const auto& rhs) {
        return lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second < rhs.second;
    };
    ranges::sort(sorted_by_xy);
    ranges::sort(sorted_by_yx, cmp_yx);
    int q;
    cin >> q;
    for (int x1, y1, x2, y2; q--;) {
        cin >> x1 >> y1 >> x2 >> y2;
        const auto ans = ranges::upper_bound(sorted_by_xy, pair(x1, y2)) - ranges::lower_bound(sorted_by_xy, pair(x1, y1)) 
                       + ranges::upper_bound(sorted_by_xy, pair(x2, y2)) - ranges::lower_bound(sorted_by_xy, pair(x2, y1))
                       + ranges::upper_bound(sorted_by_yx, pair(x2 - 1, y1), cmp_yx) - ranges::lower_bound(sorted_by_yx, pair(x1 + 1, y1), cmp_yx) 
                       + ranges::upper_bound(sorted_by_yx, pair(x2 - 1, y2), cmp_yx) - ranges::lower_bound(sorted_by_yx, pair(x1 + 1, y2), cmp_yx);
        cout << ans << '\n';
    }
}
