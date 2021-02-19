#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BIT {
    vector<T> vt;
    int n;

    BIT(int n) : vt(n + 1), n(n) {}
    void update(int i, T val) {
        for (++i; i <= n; i += i & -i)
            vt[i] += val;
    }
    T query(int i) {
        T ret = 0;
        for (; i; i &= i - 1)
            ret += vt[i];
        return ret;
    }
    T query(int l, int r) {
        return query(r) - query(l);
    }
};

void solve() {
    int n, p, q;
    cin >> n >> p >> q;

    BIT<int> bit(n);
    for (int m = p + q, x, y; m--;) {
        char op;
        cin >> op >> x >> y, --x;
        if (op == 'P')
            bit.update(x, y);
        else
            cout << bit.query(x, y) << '\n';
    }
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