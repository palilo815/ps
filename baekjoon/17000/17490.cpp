#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 1e6;

int a[mxN];
bool block[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    ll K;
    cin >> N >> M >> K;

    if (!M) return cout << "YES", 0;

    for (int i = 0; i < N; ++i)
        cin >> a[i];

    for (int u, v; M--;) {
        cin >> u >> v;
        if (u > v) swap(u, v);
        block[u == 1 && v == N ? 0 : u] = true;
    }

    ll use = 0;
    int zero = find(block, block + N, true) - block;

    for (int i = zero, j, mn;; i = j) {
        for (j = i + 1 == N ? 0 : i + 1, mn = a[i]; j != zero && !block[j]; j = j + 1 == N ? 0 : j + 1)
            mn = min(mn, a[j]);
        if ((K -= mn) < 0) return cout << "NO", 0;
        if (j == zero) break;
    }
    cout << "YES";
}