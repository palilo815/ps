#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    int k;
    cin >> k;
    vector<vector<int>> recipes(n);
    for (int l, m; k--;) {
        cin >> l >> m, --l;
        recipes[l].resize(m);
        for (auto& x : recipes[l]) {
            cin >> x, --x;
        }
    }
    const auto lim {accumulate(a.begin(), a.end(), 0)};
    auto parametric {[&]<typename T>(T lo, T hi) {
        vector<int64_t> need(n);
        auto f {[&](T mid) -> bool {
            fill(need.begin(), prev(need.end()), 0);
            need[n - 1] = mid;
            for (int i = n; i--;) {
                if (a[i] >= need[i]) continue;
                if (recipes[i].empty() || need[i] > lim) return false;
                const auto over {need[i] - a[i]};
                for (const auto& x : recipes[i]) {
                    need[x] += over;
                }
            }
            return true;
        }};
        while (lo != hi) {
            const auto mid {hi - (hi - lo) / 2};
            f(mid) ? lo = mid : hi = mid - 1;
        }
        return lo;
    }};
    cout << parametric(a[n - 1], lim);
}
