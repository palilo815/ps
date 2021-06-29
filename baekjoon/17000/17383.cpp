#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    auto parametric = [&](auto lo, auto hi) {
        auto f = [&](auto mid) -> bool {
            int64_t small = 0, need = 0;
            for (const auto& x : a) {
                int block = (x + mid - 1) / mid;
                if (block == 1)
                    ++small;
                else
                    need += need ? block - 2 : block - 1;
            }
            return small >= need;
        };

        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };

    auto [mn, mx] = minmax_element(a.begin(), a.end());
    cout << parametric(*mn, *mx);
}