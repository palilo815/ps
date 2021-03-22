#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    auto valid = [&](int mid) {
        auto prv = INT_MIN, sz = 0;
        for (const auto& x : a)
            if (prv + mid <= x) {
                prv = x;
                if (++sz == k) return true;
            }
        return false;
    };

    int lo = 0, hi = 1e9;
    while (lo != hi) {
        auto mid = lo + hi + 1 >> 1;
        valid(mid) ? lo = mid : hi = mid - 1;
    }
    cout << lo;
}