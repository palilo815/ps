#include <bits/stdc++.h>
#define val first
#define idx second
using namespace std;
using p = pair<int, int>;

const int mxN = 1e5;
const int mxR = 17;
const int mxC = 131072;

p a[mxN];
int tr[mxR][mxC];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    if (N == 1) {
        cin >> N;
        while (M--) cout << N << '\n';
        return 0;
    }

    for (int i = 0; i < N; ++i) {
        cin >> a[i].val;
        a[i].idx = i;
    }

    int R = 32 - __builtin_clz(N - 1);
    int C = 1 << R;

    sort(a, a + N);
    for (int i = 0; i < N; ++i)
        tr[0][i] = a[i].idx;
    memset(tr[0] + N, 0x3f, sizeof(int) * (C - N));

    for (int r = 0, k = 1; r + 1 < R; ++r, k <<= 1)
        for (int* t = tr[r]; t < tr[r] + C; t += k << 1)
            merge(t, t + k, t + k, t + k + k, t + mxC);

    for (int i, j, k, lo, hi, r; M--;) {
        cin >> i >> j >> k;
        lo = 0, hi = C, r = R - 1;
        for (--i, --j; ~r; --r) {
            int m = (lo + hi) >> 1;
            int cnt = upper_bound(tr[r] + lo, tr[r] + m, j) -
                      lower_bound(tr[r] + lo, tr[r] + m, i);
            k > cnt ? (lo = m, k -= cnt) : (hi = m);
        }
        cout << a[lo].val << '\n';
    }
    return 0;
}