#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, t;
    cin >> n >> t;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> b(a.size());
    auto valid = [&](auto mx_gap) {
        copy(a.begin(), a.end(), b.begin());
        for (int i = 0; i < n - 1; ++i)
            if (b[i] + mx_gap < b[i + 1])
                b[i + 1] = b[i] + mx_gap;
        for (int i = n - 1; i; --i)
            if (b[i] + mx_gap < b[i - 1])
                b[i - 1] = b[i] + mx_gap;

        for (int i = 0, use = 0; i < n; ++i) {
            use += a[i] - b[i];
            if (use > t) return false;
        }
        return true;
    };

    auto lo = 0, hi = int(1e9) - 1;
    while (lo != hi) {
        auto mid = (lo + hi) >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }

    for (int i = 0; i < n - 1; ++i)
        if (a[i] + lo < a[i + 1])
            a[i + 1] = a[i] + lo;
    for (int i = n - 1; i; --i)
        if (a[i] + lo < a[i - 1])
            a[i - 1] = a[i] + lo;

    for (const auto& x : a)
        cout << x << ' ';
}