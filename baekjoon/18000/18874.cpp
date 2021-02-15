#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> tr;
    int n;

    BIT(int n) : n(n), tr(n + 1) {}
    void update(int i) {
        for (++i; i <= n; i += i & -i)
            ++tr[i];
    }
    int query(int r) const {
        int ret = 0;
        for (; r; r -= r & -r)
            ret += tr[r];
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    BIT bit(n + 1);
    vector<int64_t> cnt(n + 1);
    for (int i = 0, h; i < n; ++i) {
        cin >> h;
        cnt[h] += bit.query(n - h);
        bit.update(n - h);
    }

    int64_t ans = 0;
    for (int i = 0; i < n; ++i) {
        cout << ans << '\n';
        ans += cnt[i];
    }
}