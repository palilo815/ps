#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_N = 1000000;

int arr[max_N];
ll segT[1048576 * 2 - 1];
int lazy[1048576 * 2 - 1];

ll build_segT(int l, int r, int idx)
{
    if (l == r) return segT[idx] = arr[l];
    int m = l + (r - l) / 2;
    return segT[idx] = build_segT(l, m, 2 * idx + 1) + build_segT(m + 1, r, 2 * idx + 2);
}
ll query(int ql, int qr, int l, int r, int idx)
{
    if (lazy[idx]) {
        segT[idx] += (ll)lazy[idx] * (r - l + 1);
        if (l != r) {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    if (ql <= l && r <= qr) return segT[idx];
    if (qr < l || r < ql) return 0;
    int m = l + (r - l) / 2;
    return query(ql, qr, l, m, 2 * idx + 1) + query(ql, qr, m + 1, r, 2 * idx + 2);
}
void update(int ql, int qr, int qv, int l, int r, int idx)
{
    if (lazy[idx]) {
        segT[idx] += (ll)lazy[idx] * (r - l + 1);
        if (l != r) {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    if (ql <= l && r <= qr) {
        segT[idx] += (ll)qv * (r - l + 1);
        if (l != r) {
            lazy[2 * idx + 1] += qv;
            lazy[2 * idx + 2] += qv;
        }
        return;
    }
    if (qr < l || r < ql) return;
    int m = l + (r - l) / 2;
    update(ql, qr, qv, l, m, 2 * idx + 1);
    update(ql, qr, qv, m + 1, r, 2 * idx + 2);
    segT[idx] = segT[2 * idx + 1] + segT[2 * idx + 2];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q, Q2; cin >> N >> Q >> Q2;
    Q += Q2;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];

    build_segT(0, N - 1, 0);

    while (Q--) {
        int q, a, b; cin >> q >> a >> b;
        // query 1 : arr[a-1,b-1] += v
        if (q == 1) {
            int v; cin >> v;
            update(a - 1, b - 1, v, 0, N - 1, 0);
        }
        // query 2 : cout << sum(arr[a-1,b-1])
        else cout << query(a - 1, b - 1, 0, N - 1, 0) << '\n';
    }
    return 0;
}