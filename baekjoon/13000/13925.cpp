#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
#define m ((l+r)>>1)
using namespace std;
using ll = long long;

const int seg_N = 131072;
const int mod = 1e9 + 7;

int segT[seg_N << 1], a[seg_N << 1], b[seg_N << 1];

void init() {
    int N; cin >> N;
    for (int i = seg_N; i < seg_N + N; ++i)
        cin >> segT[i];
    for (int i = seg_N - 1; i; --i)
        segT[i] = (segT[left] + segT[right]) % mod;
    fill_n(a, seg_N + N, 1);
}
int sum(int i, int k) {
    return ((ll)a[i] * segT[i] + (ll)b[i] * k) % mod;
}
void prop(int i, int k) {
    segT[i] = sum(i, k);
    if (k ^ 1) {
        a[left] = (ll)a[i] * a[left] % mod;
        b[left] = ((ll)a[i] * b[left] + b[i]) % mod;
        a[right] = (ll)a[i] * a[right] % mod;
        b[right] = ((ll)a[i] * b[right] + b[i]) % mod;
    }
    a[i] = 1, b[i] = 0;
}
void update(int l, int r, int ql, int qr, int qa, int qb, int i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        a[i] = (ll)a[i] * qa % mod;
        b[i] = ((ll)b[i] * qa + qb) % mod;
        return;
    }
    if (a[i] ^ 1 || b[i]) prop(i, r - l);

    update(l, m, ql, qr, qa, qb, left), update(m, r, ql, qr, qa, qb, right);
    segT[i] = (sum(left, (r - l) >> 1) + sum(right, (r - l) >> 1)) % mod;
}
int query(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return sum(i, r - l);
    if (a[i] ^ 1 || b[i]) prop(i, r - l);

    return (query(l, m, ql, qr, left) + query(m, r, ql, qr, right)) % mod;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    init();

    int M; cin >> M;
    for (int i = 0, q, l, r, v; i < M; ++i) {
        cin >> q >> l >> r;
        --l;
        switch (q) {
        case 1: cin >> v; update(0, seg_N, l, r, 1, v, 1); break;
        case 2: cin >> v; update(0, seg_N, l, r, v, 0, 1); break;
        case 3: cin >> v; update(0, seg_N, l, r, 0, v, 1); break;
        default: cout << query(0, seg_N, l, r, 1) << '\n';
        }
    }
    return 0;
}