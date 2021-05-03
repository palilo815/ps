#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<int> l(n), r(m);
    for (auto& x : l) cin >> x;
    for (auto& x : r) cin >> x;

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    if (n > m) swap(n, m), swap(l, r);

    auto ok = [&](int lim) {
        int ptr = 0;
        for (const auto& x : l) {
            while (ptr < m && r[ptr] + lim < x) ++ptr;
            if (ptr == m || x + lim < r[ptr]) return false;
            ++ptr;
        }
        return true;
    };

    int lo = 0, hi = int(1e9) - 1;
    while (lo != hi) {
        int mid = (lo + hi) >> 1;
        ok(mid) ? hi = mid : lo = mid + 1;
    }
    cout << lo;
}