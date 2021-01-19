#include <bits/stdc++.h>
using namespace std;

const int mxK = 50;

int a[mxK];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < k; ++i)
        cin >> a[i];

    auto valid = [&](int mid) {
        int cnt = m - 1;
        for (int i = 1, prv = a[0]; i < k; ++i)
            if (a[i] - prv >= mid) {
                if (!--cnt) return true;
                prv = a[i];
            }
        return false;
    };

    int lo = 1, hi = 1e6;
    while (lo != hi) {
        int mid = (lo + hi + 1) >> 1;
        valid(mid) ? lo = mid : hi = mid - 1;
    }

    for (int i = 0, cnt = m, prv = -lo; i < k; ++i)
        if (cnt && a[i] - prv >= lo) {
            cout << 1;
            prv = a[i];
            --cnt;
        } else
            cout << 0;
}