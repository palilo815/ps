#include <bits/stdc++.h>
using namespace std;

const int mxK = 1e4;

unsigned a[mxK];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int k, n;
    cin >> k >> n;

    for (int i = 0; i < k; ++i)
        cin >> a[i];

    auto valid = [&](unsigned mid) {
        int cnt = 0;
        for (int i = 0; i < k; ++i)
            if ((cnt += a[i] / mid) >= n)
                return true;
        return false;
    };

    unsigned lo = 0, hi = INT_MAX;
    while (lo != hi) {
        unsigned mid = (lo + hi + 1) >> 1;
        valid(mid) ? lo = mid : hi = mid - 1;
    }
    cout << lo;
}