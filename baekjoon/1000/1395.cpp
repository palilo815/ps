#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int segT[131072 * 2 - 1];
bool lazy[131072 * 2 + 1];

void update(int ql, int qr, int l, int r, int idx)
{
    if (lazy[idx]) {
        segT[idx] = (r - l + 1) - segT[idx];
        if (l != r) {
            lazy[2 * idx + 1] = !lazy[2 * idx + 1];
            lazy[2 * idx + 2] = !lazy[2 * idx + 2];
        }
        lazy[idx] = false;
    }
    if (ql <= l && r <= qr) {
        segT[idx] = (r - l + 1) - segT[idx];
        if (l != r) {
            lazy[2 * idx + 1] = !lazy[2 * idx + 1];
            lazy[2 * idx + 2] = !lazy[2 * idx + 2];
        }
        return;
    }
    if (qr < l || r < ql) return;
    int m = l + (r - l) / 2;
    update(ql, qr, l, m, 2 * idx + 1);
    update(ql, qr, m + 1, r, 2 * idx + 2);
    segT[idx] = segT[2 * idx + 1] + segT[2 * idx + 2];
}
int query(int ql, int qr, int l, int r, int idx)
{
    if (lazy[idx]) {
        segT[idx] = (r - l + 1) - segT[idx];
        if (l != r) {
            lazy[2 * idx + 1] = !lazy[2 * idx + 1];
            lazy[2 * idx + 2] = !lazy[2 * idx + 2];
        }
        lazy[idx] = false;
    }
    if (ql <= l && r <= qr) return segT[idx];
    if (qr < l || r < ql) return 0;
    int m = l + (r - l) / 2;
    return query(ql, qr, l, m, 2 * idx + 1) + query(ql, qr, m + 1, r, 2 * idx + 2);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    while (Q--) {
        int q, ql, qr; cin >> q >> ql >> qr;
        --ql, --qr;
        if (q) cout << query(ql, qr, 0, N - 1, 0) << '\n';
        else update(ql, qr, 0, N - 1, 0);
    }
    return 0;
}