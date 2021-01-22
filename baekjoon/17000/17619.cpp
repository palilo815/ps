#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct elem {
    int l, r, i;
};

elem a[mxN];
int idx[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;

    for (int i = 0, y; i < n; ++i)
        cin >> a[i].l >> a[i].r >> y, a[i].i = i;

    sort(a, a + n, [&](auto& a, auto& b) {
        return a.l < b.l;
    });

    for (int i = 0, prv = -1, num = -1; i < n; ++i) {
        if (prv < a[i].l) ++num;
        idx[a[i].i] = num;
        prv = max(prv, a[i].r);
    }

    for (int u, v; q--;) {
        cin >> u >> v;
        cout << (idx[u - 1] == idx[v - 1]) << '\n';
    }
}