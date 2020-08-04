#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
const int mxD = 17;
const int sgN = 1 << mxD;

int d;
int segT[mxD + 1][sgN];

int query(int l, int r, int k) {
    int ret = 0;
    for (int i = d, w = 1; l ^ r; --i, w <<= 1) {
        if (l & w) {
            ret += segT[i] + l + w - upper_bound(segT[i] + l, segT[i] + l + w, k);
            l += w;
        }
        if (r & w) {
            r -= w;
            ret += segT[i] + r + w - upper_bound(segT[i] + r, segT[i] + r + w, k);
        }
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    d = 32 - __builtin_clz(N - 1);
    for (int i = 0; i < N; ++i)
        cin >> segT[d][i];
    for (int i = d, k = 1; i; --i, k <<= 1)
        for (int j = 0; j < N; j += k << 1)
            merge(segT[i] + j, segT[i] + j + k, segT[i] + j + k, segT[i] + j + k + k, segT[i - 1] + j);

    int Q; cin >> Q;
    for (int i = 0, ans = 0, l, r, k; i < Q; ++i) {
        cin >> l >> r >> k;
        l ^= ans, r ^= ans, k ^= ans; --l;
        cout << (ans = query(l, r, k)) << '\n';
    }
    return 0;
}