#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int MX_N = 2e3;
    array<int, MX_N> a, id;
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        iota(id.begin(), id.begin() + n, 0);
        sort(id.begin(), id.begin() + n, [&](const auto& lhs, const auto& rhs) {
            return tie(a[lhs], lhs) < tie(a[rhs], rhs);
        });
        int ans = 0;
        for (int i = 1; i < n - 1; ++i) {
            const int my_id = id[i], my_val = a[id[i]];
            for (int l = i - 1, r = i + 1, l2, r2; l != -1 && r != n;) {
                if (my_val - a[id[l]] < a[id[r]] - my_val) {
                    --l;
                } else if (my_val - a[id[l]] > a[id[r]] - my_val) {
                    ++r;
                } else {
                    int c0 = 0, c1 = 0;
                    for (l2 = l; l2 != -1 && a[id[l]] == a[id[l2]]; --l2) {
                        id[l2] < my_id ? ++c0 : ++c1;
                    }
                    for (r2 = r; r2 != n && a[id[r]] == a[id[r2]]; ++r2) {
                        ans += id[r2] < my_id ? c1 : c0;
                    }
                    l = l2, r = r2;
                }
            }
        }
        cout << ans << '\n';
    }
}