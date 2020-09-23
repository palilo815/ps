#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
struct line {
    unsigned x, l;
};

const int mxN = 1e5;

int N;
line a[mxN];

bool solve(unsigned m) {
    unsigned pos = a[0].x;
    for (int i = 1; i < N; ++i) {
        if (pos + m > a[i].x + a[i].l) return false;
        pos = max(pos + m, a[i].x);
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N;
    loop(i, N) cin >> a[i].x >> a[i].l;

    sort(a, a + N, [&](auto& a, auto& b) {
        return a.x < b.x;
    });

    unsigned lo = 0, hi = a[N - 1].x + a[N - 1].l;
    while (lo ^ hi) {
        unsigned m = (lo + hi + 1) >> 1;
        solve(m) ? (lo = m) : (hi = m - 1);
    }
    cout << lo;
    return 0;
}