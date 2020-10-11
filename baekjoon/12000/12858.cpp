#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;
using ll = long long;

const int mxN = 1e5;
const int sgN = 131072;

int N;
ll segT[sgN << 1], bit[mxN + 1];

void u_bit(int i, int val) {
    for (; i <= N; i += i & -i)
        bit[i] += val;
}
ll q_bit(int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += bit[i];
    return ret;
}
void u_seg(int i, ll val) {
    segT[i += sgN] = val;
    while (i >>= 1)
        segT[i] = gcd(segT[left], segT[right]);
}
ll q_seg(int l, int r) {
    ll ret = 0;
    for (l += sgN, r += sgN; l != r; l >>= 1, r >>= 1) {
        if (l & 1) ret = gcd(ret, segT[l++]);
        if (r & 1) ret = gcd(ret, segT[--r]);
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    // ** NOTE **
    // 1-based

    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> segT[sgN + i];

    for (int i = 1; i <= N; ++i)
        u_bit(i, segT[sgN + i]), u_bit(i + 1, -segT[sgN + i]);

    for (int i = N; i; --i)
        segT[sgN + i] = abs(segT[sgN + i] - segT[sgN + i - 1]);

    for (int i = sgN - 1; i; --i)
        segT[i] = gcd(segT[left], segT[right]);

    int Q;
    cin >> Q;

    for (int t, l, r; Q--;) {
        cin >> t >> l >> r;
        ++r;
        if (t) {
            u_bit(l, t), u_bit(r, -t);
            u_seg(l, abs(q_bit(l) - q_bit(l - 1)));
            u_seg(r, abs(q_bit(r) - q_bit(r - 1)));
        } else
            cout << gcd(q_bit(l), q_seg(l + 1, r)) << '\n';
    }
    return 0;
}