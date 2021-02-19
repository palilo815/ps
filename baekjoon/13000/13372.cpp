#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> vt;
    int n;

    BIT(int n) : vt(n + 1), n(n) {}
    void add(int i) {
        for (++i; i <= n; i += i & -i)
            ++vt[i];
    }
    int query(int i) {
        int ret = 0;
        for (; i; i &= i - 1)
            ret += vt[i];
        return ret;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x, x = n - x;

    BIT bit(n);
    int64_t ans = 0;
    for (const auto& x : a) {
        ans += bit.query(x);
        bit.add(x);
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}