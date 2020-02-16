#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int arr[max_N + 1];
int lazy[131072 * 2 - 1];

// [ql,qr] 구간에 전부 + qv
void update(int ql, int qr, int qv, int l, int r, int idx)
{
    if (lazy[idx]) {
        if (l == r) arr[l] += lazy[idx];
        else {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    if (ql <= l && r <= qr) {
        lazy[idx] += qv;
        return;
    }
    if (qr < l || r < ql) return;
    int m = l + (r - l) / 2;
    update(ql, qr, qv, l, m, 2 * idx + 1);
    update(ql, qr, qv, m + 1, r, 2 * idx + 2);
}
// return arr[qi]
int query(int qi, int l, int r, int idx)
{
    if (lazy[idx]) {
        if (l == r) arr[l] += lazy[idx];
        else {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    if (l == r) return arr[l];
    int m = l + (r - l) / 2;
    if (qi <= m) return query(qi, l, m, 2 * idx + 1);
    else return query(qi, m + 1, r, 2 * idx + 2);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];

    int Q; cin >> Q;
    while (Q--) {
        int q; cin >> q;
        if (q == 1) {
            int ql, qr, qv; cin >> ql >> qr >> qv;
            update(ql - 1, qr - 1, qv, 0, N - 1, 0);
        }
        else {
            int qi; cin >> qi;
            cout << query(qi - 1, 0, N - 1, 0) << '\n';
        }
    }
    return 0;
}