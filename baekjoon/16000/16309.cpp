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

    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) cin >> x >> y;

    auto parametric = [&](auto lo, auto hi) {
        auto f = [&](auto mid) -> bool {
            int64_t sum = 0;
            for (const auto& [x, y] : a)
                if (auto earn = int64_t(x) * mid - y; earn > 0)
                    if ((sum += earn) >= m)
                        return true;
            return false;
        };

        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };

    cout << parametric(1, int(2e9));
}