#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int N, M, a[mxN];
bitset<500001> ck;

bool solve(int m) {
    ck.reset();
    int cnt = 0;
    for (int i = 0, j = 0; j < N;) {
        while (ck[a[j]]) ck[a[i++]] = 0;
        ck[a[j++]] = 1;

        if (j - i == m) {
            if (++cnt == M) return true;
            while (i ^ j) ck[a[i++]] = 0;
        }
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
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    int lo = 1, hi = N / M;
    while (lo ^ hi) {
        int m = (lo + hi + 1) >> 1;
        solve(m) ? (lo = m) : (hi = m - 1);
    }
    cout << lo;
    return 0;
}