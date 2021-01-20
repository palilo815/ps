#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;
const int mxS = 20;

struct component {
    char type[mxS + 1];
    int p, q;
};

component a[mxN + 1];

void solve() {
    int n, m;
    cin >> n >> m;

    char buf[mxS + 1];
    for (int i = 0; i < n; ++i)
        cin >> a[i].type >> buf >> a[i].p >> a[i].q;

    sort(a, a + n, [&](auto& a, auto& b) {
        return strcmp(a.type, b.type) < 0;
    });
    a[n].type[0] = '#';

    auto valid = [&](int mid) {
        for (int i = 0, j = 0, budget = m, buy; i < n; i = j) {
            // a[n] is sentinel
            buy = a[i].q >= mid ? a[i].p : 1e9;
            for (++j; !strcmp(a[i].type, a[j].type); ++j)
                if (a[j].q >= mid)
                    buy = min(buy, a[j].p);
            if ((budget -= buy) < 0) return false;
        }
        return true;
    };

    int lo = 0, hi = 1e9;
    while (lo != hi) {
        int mid = (lo + hi + 1) >> 1;
        valid(mid) ? lo = mid : hi = mid - 1;
    }
    cout << lo << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}