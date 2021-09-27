#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    int64_t s, t;
    cin >> n >> q >> s >> t;
    vector<int64_t> a(n);
    {
        int prv, cur;
        cin >> prv;
        for (auto& x : a) {
            cin >> cur;
            x = cur - prv;
            prv = cur;
        }
    }
    int64_t res = 0;
    for (const auto& x : a) {
        res -= (x < 0 ? t : s) * x;
    }
    for (int l, r, x; q--;) {
        cin >> l >> r >> x, --l;
        res += (a[l] < 0 ? t : s) * a[l];
        a[l] += x;
        res -= (a[l] < 0 ? t : s) * a[l];
        if (r != n) {
            res += (a[r] < 0 ? t : s) * a[r];
            a[r] -= x;
            res -= (a[r] < 0 ? t : s) * a[r];
        }
        cout << res << '\n';
    }
}