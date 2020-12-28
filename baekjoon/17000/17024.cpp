#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int cnt[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        ++cnt[u - 1], ++cnt[v - 1];
    }

    cout << 1 + *max_element(cnt, cnt + n);
}