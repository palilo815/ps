#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e6;

int idx[mxN], to[mxN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        idx[x - 1] = i;
    }
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        to[idx[x - 1]] = i;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (to[i] == -1) continue;
        int j = to[i], cnt = 0, k;
        for (to[i] = -1; i != j; ++cnt, j = k) {
            k = to[j];
            to[j] = -1;
        }
        ans += cnt;
    }
    cout << ans;
}