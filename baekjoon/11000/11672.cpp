#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 2e5;

struct BIT {
    int n, tr[mxN + 1];
    BIT(int n) : n(n + 1) {}
    void clear() {
        memset(tr, 0, sizeof(int) * n);
    }
    void update(int i) {
        for (; i < n; i += i & -i)
            ++tr[i];
    }
    int query(int i) {
        int ret = 0;
        for (; i; i -= i & -i)
            ret += tr[i];
        return ret;
    }
};

int a[mxN], b[mxN], c[mxN], idx[mxN + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    loop(i, n) cin >> a[i];
    loop(i, n) cin >> b[i];
    loop(i, n) cin >> c[i];

    int64_t ans = 0;
    BIT bit(n);

    bit.clear();
    loop(i, n) idx[a[i]] = i + 1;
    for (int i = n - 1; ~i; --i) {
        ans += bit.query(idx[b[i]]);
        bit.update(idx[b[i]]);
    }

    bit.clear();
    loop(i, n) idx[b[i]] = i + 1;
    for (int i = n - 1; ~i; --i) {
        ans += bit.query(idx[c[i]]);
        bit.update(idx[c[i]]);
    }

    bit.clear();
    loop(i, n) idx[c[i]] = i + 1;
    for (int i = n - 1; ~i; --i) {
        ans += bit.query(idx[a[i]]);
        bit.update(idx[a[i]]);
    }

    cout << ((int64_t)n * (n - 1) - ans) / 2;
}