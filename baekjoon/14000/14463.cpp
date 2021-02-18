#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> tree;
    int n;
    BIT(int n) : tree(n + 1), n(n) {}
    void update(int i) {
        for (++i; i <= n; i += i & -i)
            ++tree[i];
    }
    int query(int i) {
        int ret = 0;
        for (; i; i -= i & -i)
            ret += tree[i];
        return ret;
    }
    int query(int l, int r) {
        return query(r) - query(l);
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

    vector<pair<int, int>> a(n);
    for (int i = 1, x; i <= n << 1; ++i) {
        cin >> x, --x;
        (a[x].first ? a[x].second : a[x].first) = i;
    }

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    BIT bit(n << 1);
    int ans = 0;
    for (const auto& [in, out] : a) {
        ans += bit.query(in + 1, out);
        bit.update(out);
    }
    cout << ans;
}