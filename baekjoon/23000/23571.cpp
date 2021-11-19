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
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    auto parametric = [&](auto lo, auto hi) {
        auto f = [&](auto mid) -> bool {
            auto same = [&](const auto& x, const auto& y) { return abs(x - y) <= mid; };
            const auto l = mismatch(a.begin(), prev(a.end()), b.begin(), same);
            const auto r = mismatch(a.rbegin(), make_reverse_iterator(next(l.first)), b.rbegin(), same);
            return equal(l.first, prev(r.first.base()), next(l.second), same) ||
                   equal(next(l.first), r.first.base(), l.second, same);
        };
        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };
    const auto best = parametric(0, int(1e9));
    auto same = [&](const auto& x, const auto& y) { return abs(x - y) <= best; };
    const auto base = mismatch(a.rbegin(), prev(a.rend()), b.rbegin(), same);
    const auto ans1 = [&]() {
        // case 1:  || \\\\ ||
        auto [i, j] = mismatch(next(base.first), a.rend(), base.second, same);
        return equal(i, a.rend(), next(j), same) ? *base.first : INT_MAX;
    }();
    const auto ans2 = [&]() {
        // case 1:  || //// ||
        auto [i, j] = mismatch(base.first, prev(a.rend()), next(base.second), same);
        return equal(next(i), a.rend(), j, same) ? *i : INT_MAX;
    }();
    cout << min(ans1, ans2);
}