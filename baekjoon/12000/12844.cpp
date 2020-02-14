#include <bits/stdc++.h>
using namespace std;

const int max_N = 500000;

int arr[max_N];
int segT[524288 * 2 - 1];
int lazy[524288 * 2 - 1];

int build_segT(int l, int r, int idx)
{
    if (l == r) return segT[idx] = arr[l];
    int m = l + (r - l) / 2;
    return segT[idx] = build_segT(l, m, 2 * idx + 1) ^ build_segT(m + 1, r, 2 * idx + 2);
}
int query(int ql, int qr, int l, int r, int idx)
{
    if (lazy[idx]) {
        if ((r - l + 1) % 2) segT[idx] ^= lazy[idx];
        if (l != r) {
            lazy[2 * idx + 1] ^= lazy[idx];
            lazy[2 * idx + 2] ^= lazy[idx];
        }
        lazy[idx] = 0;
    }

    if (ql <= l && r <= qr) return segT[idx];
    if (qr < l || r < ql) return 0;
    int m = l + (r - l) / 2;
    return query(ql, qr, l, m, 2 * idx + 1) ^ query(ql, qr, m + 1, r, 2 * idx + 2);
}
void update(int ql, int qr, int qv, int l, int r, int idx)
{
    if (lazy[idx]) {
        if ((r - l + 1) % 2) segT[idx] ^= lazy[idx];
        if (l != r) {
            lazy[2 * idx + 1] ^= lazy[idx];
            lazy[2 * idx + 2] ^= lazy[idx];
        }
        lazy[idx] = 0;
    }

    if (ql <= l && r <= qr) {
        if ((r - l + 1) % 2) segT[idx] ^= qv;
        if (l != r) {
            lazy[2 * idx + 1] ^= qv;
            lazy[2 * idx + 2] ^= qv;
        }
        return;
    }
    if (qr < l || r < ql) return;
    int m = l + (r - l) / 2;
    update(ql, qr, qv, l, m, 2 * idx + 1);
    update(ql, qr, qv, m + 1, r, 2 * idx + 2);
    segT[idx] = segT[2 * idx + 1] ^ segT[2 * idx + 2];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];

    build_segT(0, N - 1, 0);

    int Q; cin >> Q;
    while (Q--) {
        int q, a, b; cin >> q >> a >> b;
        if (a > b) swap(a, b);
        if (q == 1) {
            int c; cin >> c;
            update(a, b, c, 0, N - 1, 0);
        }
        else cout << query(a, b, 0, N - 1, 0) << '\n';
    }
    return 0;
}