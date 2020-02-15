#include <bits/stdc++.h>
using namespace std;

const int max_N = 500000;

int arr[max_N + 1];
int segT[524288 * 2 - 1];

int build_segT(int l, int r, int idx)
{
    if (l == r) return segT[idx] = arr[l];
    int m = l + (r - l) / 2;
    return segT[idx] = build_segT(l, m, 2 * idx + 1) + build_segT(m + 1, r, 2 * idx + 2);
}
void update(int qi, int qv, int l, int r, int idx)
{
    segT[idx] += qv;
    if (l == r) return;
    int m = l + (r - l) / 2;
    if (qi <= m) update(qi, qv, l, m, 2 * idx + 1);
    else update(qi, qv, m + 1, r, 2 * idx + 2);
}
int query(int k, int l, int r, int idx)
{
    if (l == r) return l;
    int m = l + (r - l) / 2;
    if (segT[2 * idx + 1] >= k) return query(k, l, m, 2 * idx + 1);
    else return query(k - segT[2 * idx + 1], m + 1, r, 2 * idx + 2);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> arr[i];

    build_segT(0, N - 1, 0);

    int Q; cin >> Q;
    while (Q--) {
        int q, a; cin >> q >> a;
        if (q == 1) {
            int b; cin >> b;
            update(a - 1, b, 0, N - 1, 0);
        }
        else cout << query(a, 0, N - 1, 0) + 1 << '\n';
    }
    return 0;
}