#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto parametric = [&]<typename T>(T lo, T hi) {
        auto f = [&](T mid) -> bool {
            int64_t balloon = 0;
            return ranges::any_of(a, [&](const auto& t) {
                return (balloon += mid / t) >= m;
            });
        };
        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        // // last true
        // while (lo != hi) {
        //     auto mid = hi - (hi - lo) / 2;
        //     f(mid) ? lo = mid : hi = mid - 1;
        // }
        return lo;
    };
    cout << parametric(int64_t(1), int64_t(1e12));
}
