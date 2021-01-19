#include <bits/stdc++.h>
using namespace std;

const int mxM = 1e4;

short a[mxM];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i)
        cin >> a[i];

    auto valid = [&](int64_t mid) {
        int64_t cnt = 0;
        for (int i = 0; i < m; ++i)
            if ((cnt += mid / a[i] + 1) >= n)
                return true;
        return false;
    };

    int64_t lo = 0, hi = 6e10;
    while (lo != hi) {
        int64_t mid = (lo + hi) >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    if (!lo) return cout << n, 0;

    vector<int> vt;
    for (int i = 0; i < m; ++i) {
        n -= (lo - 1) / a[i] + 1;
        if (lo % a[i] == 0) vt.emplace_back(i + 1);
    }
    cout << vt[n - 1];
}