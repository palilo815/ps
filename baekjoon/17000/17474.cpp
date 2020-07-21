#include <bits/stdc++.h>
#define m ((l+r)>>1)
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using ll = long long;

const int max_N = 1e6;
const int seg_N = 1048576;

int max1[seg_N << 1], max2[seg_N << 1], cnt[seg_N << 1];
ll sum[seg_N << 1];

void build(int i) {
    sum[i] = sum[left] + sum[right];
    if (max1[left] == max1[right]) {
        max1[i] = max1[left];
        max2[i] = max(max2[left], max2[right]);
        cnt[i] = cnt[left] + cnt[right];
    }
    else {
        int n = max1[left] > max1[right] ? left : right;
        max1[i] = max1[n];
        max2[i] = max(max1[n ^ 1], max(max2[n], max2[n ^ 1]));
        cnt[i] = cnt[n];
    }
}
void init() {
    int N; cin >> N;
    for (int i = seg_N; i < seg_N + N; ++i)
        cin >> max1[i];

    memset(max1 + seg_N + N, -1, sizeof(int) * (seg_N - N));
    memset(max2 + seg_N, -1, sizeof(int) * seg_N);
    fill_n(cnt + seg_N, N, 1);
    for (int i = seg_N; i < seg_N + N; ++i)
        sum[i] = max1[i];

    for (int i = seg_N - 1; i; --i)
        build(i);
}
void prop(int i) {
    int qv = max1[i];
    if (qv < max1[left]) {
        sum[left] -= (ll)cnt[left] * (max1[left] - qv);
        max1[left] = qv;
    }
    if (qv < max1[right]) {
        sum[right] -= (ll)cnt[right] * (max1[right] - qv);
        max1[right] = qv;
    }
}
void update(int l, int r, int ql, int qr, int qv, int i) {
    if (qr <= l || r <= ql || qv >= max1[i]) return;
    if (l + 1 ^ r) prop(i);
    if (ql <= l && r <= qr && qv > max2[i]) {
        sum[i] -= (ll)cnt[i] * (max1[i] - qv);
        max1[i] = qv;
        return;
    }

    update(l, m, ql, qr, qv, left), update(m, r, ql, qr, qv, right);
    build(i);
}
int q_max(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return max1[i];
    if (l + 1 ^ r) prop(i);

    return max(q_max(l, m, ql, qr, left), q_max(m, r, ql, qr, right));
}
ll q_sum(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return sum[i];
    if (l + 1 ^ r) prop(i);

    return q_sum(l, m, ql, qr, left) + q_sum(m, r, ql, qr, right);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    init();

    int Q; cin >> Q;
    for (int i = 0, q, l, r, x; i < Q; ++i) {
        cin >> q >> l >> r; --l;
        switch (q) {
        case 2: cout << q_max(0, seg_N, l, r, 1) << '\n'; break;
        case 3: cout << q_sum(0, seg_N, l, r, 1) << '\n'; break;
        default: cin >> x; update(0, seg_N, l, r, x, 1);
        }
    }
    return 0;
}