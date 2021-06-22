#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

constexpr int MX_N = 1e4;

pair<int, int> a[MX_N];

void solve() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i)
        cin >> a[i].x >> a[i].y;

    sort(a, a + n, [&](const auto& lhs, const auto& rhs) {
        return lhs.x < rhs.x;
    });

    auto parametric = [&](auto lo, auto hi) {
        auto f = [&](auto mid) -> bool {
            int chance = k;
            for (int i = 0, j; i < n; i = j) {
                int mn = a[i].y, mx = a[i].y;
                for (j = i + 1; j < n; ++j) {
                    if (a[j].y > mx)
                        mx = a[j].y;
                    else if (a[j].y < mn)
                        mn = a[j].y;
                    if (mx - mn > mid) break;
                }
                if (chance-- == 0) return false;
            }
            return true;
        };

        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };

    auto res = parametric(0, 200000000);
    cout << (res >> 1) << '.' << (res & 1 ? 5 : 0) << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) solve();
}