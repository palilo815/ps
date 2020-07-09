#include <bits/stdc++.h>
#define L (i<<1)
#define R (i<<1|1)
using namespace std;

const int seg_N = 524288;

int N, lt[seg_N], mt[seg_N], rt[seg_N], sz[seg_N];
char lstep[seg_N], rstep[seg_N];

void init() {
    cin >> N;
    int N2 = 1;
    while (N2 < N) N2 <<= 1;
    memset(lstep, 'L', N + N2);
    memset(rstep, 'L', N + N2);

    for (int l = N2, r = N2 + N - 1; l; l >>= 1, r >>= 1) {
        fill(lt + l, lt + r + 1, 1);
        fill(mt + l, mt + r + 1, 1);
        fill(rt + l, rt + r + 1, 1);
    }

    fill(sz + N2, sz + N + N2, 1);
    for (int i = N2 - 1; i; --i)
        sz[i] = sz[L] + sz[R];
    N = N2;
}
int query(int i) {
    i += N;
    lstep[i] = rstep[i] = (lstep[i] == 'L' ? 'R' : 'L');

    for (i >>= 1; i; i >>= 1) {
        lstep[i] = lstep[L] ? lstep[L] : lstep[R];
        rstep[i] = rstep[R] ? rstep[R] : rstep[L];

        mt[i] = max({mt[L], mt[R], rstep[L] ^ lstep[R] ? rt[L] + lt[R] : 0});

        if (lt[L] == sz[L] && rstep[L] ^ lstep[R])
            lt[i] = lt[L] + lt[R];
        else lt[i] = lt[L];

        if (rt[R] == sz[R] && lstep[R] ^ rstep[L])
            rt[i] = rt[R] + rt[L];
        else rt[i] = rt[R];
    }
    return mt[1];
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    init();

    int Q; cin >> Q;
    while (Q--) {
        int i; cin >> i;
        cout << query(--i) << '\n';
    }
    return 0;
}