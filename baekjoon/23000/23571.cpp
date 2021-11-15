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
            int l = 0, r = n;
            while (l != n && abs(a[l] - b[l]) <= mid) ++l;
            while (l != r && abs(a[r - 1] - b[r - 1]) <= mid) --r;
            bool ok = true;
            for (int i = l; i < r - 1; ++i) {
                if (abs(a[i] - b[i + 1]) > mid) {
                    ok = false;
                    break;
                }
            }
            if (exchange(ok, true)) return true;
            for (int i = l + 1; i < r; ++i) {
                if (abs(a[i] - b[i - 1]) > mid) {
                    ok = false;
                    break;
                }
            }
            return ok;
        };
        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };
    const auto best = parametric(0, int(1e9));
    int r = n - 1;
    while (r && abs(a[r] - b[r]) <= best) {
        --r;
    }
    // case 1: "\\\\"
    int p1 = r, ans1 = a[p1];
    while (p1 && abs(a[p1 - 1] - b[p1]) <= best) --p1;
    for (int i = 0; i < p1; ++i) {
        if (abs(a[i] - b[i]) > best) {
            ans1 = INT_MAX;
            break;
        }
    }
    // case 2: "////"
    int p2 = r;
    while (p2 && abs(a[p2] - b[p2 - 1]) <= best) --p2;
    int ans2 = a[p2];
    for (int i = 0; i < p2; ++i) {
        if (abs(a[i] - b[i]) > best) {
            ans2 = INT_MAX;
            break;
        }
    }
    assert(ans1 != INT_MAX || ans2 != INT_MAX);
    cout << min(ans1, ans2);
}