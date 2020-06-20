#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1000000007;
const int max_N = 1000000;

int N, Q, Q2;
int segT[max_N << 1];

void init() {
    cin >> N >> Q >> Q2;
    Q += Q2;
    for (int i = N; i < N << 1; ++i)
        cin >> segT[i];
    for (int i = N - 1; i; --i)
        segT[i] = (ll)segT[i << 1] * segT[i << 1 | 1] % mod;
}
void update(int i, int v) {
    segT[i + N] = v;
    for (i += N; i > 1; i >>= 1)
        segT[i >> 1] = (ll)segT[i] * segT[i ^ 1] % mod;
}
int query(int l, int r) {
    int ret = 1;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ret = (ll)ret * segT[l++] % mod;
        if (r & 1) ret = (ll)ret * segT[--r] % mod;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    init();

    while (Q--) {
        int q, x, y; cin >> q >> x >> y;
        if (q == 1) update(x - 1, y);
        else cout << query(x - 1, y) << '\n';
    }
    return 0;
}