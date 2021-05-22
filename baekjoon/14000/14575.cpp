#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, t;
    cin >> n >> t;

    vector<pair<int, int>> a(n);
    for (auto& [l, r] : a) cin >> l >> r;

    if (accumulate(a.begin(), a.end(), 0, [&](auto& sum, auto& val) { return sum + val.first; }) > t)
        return cout << -1, 0;

    int max_l = max_element(a.begin(), a.end(), [&](auto& lhs, auto& rhs) {
        return lhs.first < rhs.first;
    })->first;
    int max_r = max_element(a.begin(), a.end(), [&](auto& lhs, auto& rhs) {
        return lhs.second < rhs.second;
    })->second;

    auto parametric = [&](auto mn, auto mx, bool impossible_case) {
        auto ok = [&](auto lim) -> bool {
            int take = 0;
            for (const auto& [l, r] : a)
                take += min(r, lim);
            return t <= take;
        };

        auto lo = mn, hi = mx + impossible_case;
        while (lo != hi) {
            int mid = (lo + hi) >> 1;
            ok(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };

    auto res = parametric(max_l, max_r, true);
    cout << (res == max_r + 1 ? -1 : res) << '\n';
}