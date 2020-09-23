#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct line {
    ll s, e;
};

const int mxN = 1e5;

line a[mxN];
int N, M;

bool solve(ll m) {
    ll cnt = (a[0].e - a[0].s) / m;
    ll pos = a[0].s + cnt * m;
    if (++cnt >= N) return true;

    for (int i = 1; i < M; ++i) {
        if (a[i].s - pos >= m) ++cnt, pos = a[i].s;
        ll c = (a[i].e - pos) / m;
        cnt += c, pos += m * c;
        if (cnt >= N) return true;
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> M;
    for (int i = 0; i < M; ++i)
        cin >> a[i].s >> a[i].e;

    sort(a, a + M, [&](auto& a, auto& b) {
        return a.s < b.s;
    });

    ll lo = 1, hi = a[M - 1].e;
    while (lo ^ hi) {
        ll m = (lo + hi + 1) >> 1;
        solve(m) ? (lo = m) : (hi = m - 1);
    }
    cout << lo;
    return 0;
}