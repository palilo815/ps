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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, x;
    cin >> n >> x;

    BIT bit(n << 1 | 1);
    bit.add(n);

    int64_t ans = 0;
    for (int h, sum = n; n--;) {
        cin >> h;
        sum += h >= x ? 1 : -1;
        ans += bit.query(sum + 1);
        bit.add(sum);
    }
    cout << ans;
}