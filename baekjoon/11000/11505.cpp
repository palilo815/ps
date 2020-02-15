#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1000000007;
const int max_N = 1000000;

int arr[max_N];
int segT[1048576 * 2 - 1];

int build_segT(int l, int r, int idx)
{
    if (l == r) return segT[idx] = arr[l];
    int m = l + (r - l) / 2;
    return segT[idx] = (ll)build_segT(l, m, 2 * idx + 1) * build_segT(m + 1, r, 2 * idx + 2) % mod;
}
int query(int ql, int qr, int l, int r, int idx)
{
    if (ql <= l && r <= qr) return segT[idx];
    if (qr < l || r < ql) return 1;
    int m = l + (r - l) / 2;
    return (ll)query(ql, qr, l, m, 2 * idx + 1) * query(ql, qr, m + 1, r, 2 * idx + 2) % mod;
}
void update(int qi, int qv, int l, int r, int idx)
{
    if (l == r) {
        segT[idx] = qv;
        return;
    }
    int m = l + (r - l) / 2;
    if (qi <= m) update(qi, qv, l, m, 2 * idx + 1);
    else update(qi, qv, m + 1, r, 2 * idx + 2);
    segT[idx] = (ll)segT[2 * idx + 1] * segT[2 * idx + 2] % mod;
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
        if (q == 1) update(a - 1, b, 0, N - 1, 0);
        else cout << query(a - 1, b - 1, 0, N - 1, 0) << '\n';
    }
    return 0;
}