#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e6;

unsigned a[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    unsigned m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    auto valid = [&](unsigned mid) {
        unsigned sum = 0;
        for (int i = 0; i < n; ++i)
            if (a[i] > mid && (sum += a[i] - mid) >= m)
                return true;
        return false;
    };

    unsigned lo = 0, hi = 1e9;
    while (lo != hi) {
        unsigned mid = (lo + hi + 1) >> 1;
        valid(mid) ? lo = mid : hi = mid - 1;
    }
    cout << lo;
}