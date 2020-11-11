#include <bits/stdc++.h>
using namespace std;

const int mxW = 500;

int h[mxW], L[mxW], R[mxW];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int H, W;
    cin >> H >> W;

    for (int i = 0; i < W; ++i)
        cin >> h[i];

    for (int i = 0, mx = 0; i < W; ++i) {
        L[i] = mx;
        mx = max(mx, h[i]);
    }
    for (int i = W - 1, mx = 0; ~i; --i) {
        R[i] = mx;
        mx = max(mx, h[i]);
    }

    int ans = 0;
    for (int i = 0; i < W; ++i)
        ans += max(0, min(L[i], R[i]) - h[i]);
    cout << ans;
}