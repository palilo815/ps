#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<int64_t> a(n);
    for (auto& x : a) cin >> x;

    for (int i = 1; i < n; ++i)
        a[i] ^= a[i - 1];

    // xorsum [0...r]
    auto xorsum = [&](int64_t r) -> int64_t {
        if (r < 0) return 0;
        r %= (n + 1);
        return r == n ? 0 : a[r];
    };

    int q;
    cin >> q;

    for (int64_t l, r; q--;) {
        cin >> l >> r, --l, --r;
        cout << (xorsum(l - 1) ^ xorsum(r)) << '\n';
    }
}