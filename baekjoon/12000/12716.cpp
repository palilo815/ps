#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

struct BIT {
    vector<int> vt;
    int n;

    BIT(int n) : vt(n + 1), n(n) {}
    void update(int i, int val) {
        for (++i; i <= n; i += i & -i)
            vt[i] = (vt[i] + val) % mod;
    }
    int query(int i) {
        int ret = 0;
        for (; i; i &= i - 1)
            ret = (ret + vt[i]) % mod;
        return ret;
    }
};

int solve() {
    int n, m;
    int64_t x, y, z;
    cin >> n >> m >> x >> y >> z;

    vector<int> a(m), ord(n);
    for (auto& x : a) cin >> x;

    for (int i = 0; i < n; ++i) {
        ord[i] = a[i % m];
        a[i % m] = (x * a[i % m] + y * (i + 1)) % z;
    }

    a = ord;
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    for (auto& x : a)
        x = lower_bound(ord.begin(), ord.end(), x) - ord.begin();

    BIT bit(ord.size());
    int ans = 0;
    for (const auto& x : a) {
        auto res = bit.query(x) + 1;
        ans = (ans + res) % mod;
        bit.update(x, res);
    }
    return ans;
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
        cout << "Case #" << t << ": " << solve() << '\n';
}