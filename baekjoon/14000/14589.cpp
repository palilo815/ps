#include <bits/stdc++.h>
using namespace std;

const int mxN = 15e4;
const int table_size = 18;

int jump[table_size][mxN];

struct line {
    int l, r, i;
};

line a[mxN];
int idx[mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> a[i].l >> a[i].r;
    for (int i = 0; i < n; ++i)
        a[i].i = i + 1;

    sort(a, a + n, [&](auto& a, auto& b) {
        return a.r < b.r;
    });

    for (int i = 0; i < n; ++i)
        idx[a[i].i] = i;

    for (int i = n - 1, farthest = n - 1; ~i; --i) {
        while (i != farthest && a[i].r < a[farthest].l)
            --farthest;
        jump[0][i] = i == farthest ? -1 : farthest;
    }

    int row = 32 - __builtin_clz(n);
    for (int i = 1; i < row; ++i)
        for (int j = 0; j < n; ++j)
            jump[i][j] = ~jump[i - 1][j] ? jump[i - 1][jump[i - 1][j]] : -1;

    int q;
    cin >> q;

    for (int u, v, ans; q--;) {
        cin >> u >> v;
        u = idx[u], v = idx[v];
        if (u > v) swap(u, v);
        if (a[u].r >= a[v].l) {
            cout << "1\n";
            continue;
        }

        ans = 0;
        for (int i = row - 1; ~i; --i)
            if (~jump[i][u] && a[jump[i][u]].r < a[v].l)
                ans += 1 << i, u = jump[i][u];
        cout << (~jump[0][u] ? ans + 2 : -1) << '\n';
    }
}