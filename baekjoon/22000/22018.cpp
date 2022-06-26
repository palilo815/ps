#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, d;
    cin >> n >> m >> d;
    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) {
        cin >> x >> y;
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
    });
    vector<int> values(n);
    transform(a.begin(), a.end(), values.begin(), [&](const auto& x) {
        return x.second;
    });
    sort(values.begin(), values.end());
    auto parametric = [&]<typename T>(T lo, T hi) {
        auto f = [&](T mid) -> bool {
            const auto lim {values[mid]};
            auto remain {m}, prv {-d};
            for (const auto& [x, y] : a) {
                if (y < lim || x - prv < d) continue;
                prv = x;
                if (--remain == 0) return true;
            }
            return false;
        };
        // last true
        while (lo != hi) {
            auto mid = hi - (hi - lo) / 2;
            f(mid) ? lo = mid : hi = mid - 1;
        }
        return lo;
    };
    auto res {parametric(-1, n - 1)};
    cout << (res == -1 ? -1 : values[res]);
}
