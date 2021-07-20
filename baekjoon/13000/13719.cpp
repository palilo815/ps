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
    for (auto& x : a) {
        cin >> x;
    }
    int ans = 0;
    for (int lp = 0, rp = n - 1; lp <= rp; ++lp, --rp) {
        int64_t lsum = a[lp], rsum = a[rp];
        const int lp0 = lp, rp0 = rp;
        while (lsum != rsum) {
            lsum < rsum ? lsum += a[++lp] : rsum += a[--rp];
        }
        ans += lp - lp0 + (lp0 == rp ? 0 : rp0 - rp);
    }
    cout << ans;
}