#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int arr[max_N];
int segT[131072 * 2 - 1];

int build_segT(int l, int r, int idx)
{
    if (l == r) return segT[idx] = arr[l];
    int mid = l + (r - l) / 2;
    return segT[idx] = build_segT(l, mid, 2 * idx + 1) * build_segT(mid + 1, r, 2 * idx + 2);
}
int query(int ql, int qr, int l, int r, int idx)
{
    if (ql <= l && r <= qr) return segT[idx];
    if (r < ql || qr < l) return 1;
    int mid = l + (r - l) / 2;
    return query(ql, qr, l, mid, 2 * idx + 1) * query(ql, qr, mid + 1, r, 2 * idx + 2);
}
void update(int qi, int qv, int l, int r, int idx)
{
    if (l == r) {
        arr[qi] = segT[idx] = qv;
        return;
    }
    int mid = l + (r - l) / 2;
    if (qi <= mid) update(qi, qv, l, mid, 2 * idx + 1);
    else update(qi, qv, mid + 1, r, 2 * idx + 2);
    segT[idx] = segT[2 * idx + 1] * segT[2 * idx + 2];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q;
    while (cin >> N >> Q) {
        for (int i = 0; i < N; ++i) {
            int x; cin >> x;
            if (x > 0) arr[i] = 1;
            else if (x < 0) arr[i] = -1;
            else arr[i] = 0;
        }

        build_segT(0, N - 1, 0);

        while (Q--) {
            char q; int a, b;
            cin >> q >> a >> b;
            if (q == 'C') {
                if (b > 0) b = 1;
                else if (b < 0) b = -1;
                if (arr[a - 1] != b)
                    update(a - 1, b, 0, N - 1, 0);
            }
            else {
                int res = query(a - 1, b - 1, 0, N - 1, 0);
                if (res > 0) cout << '+';
                else if (res < 0) cout << '-';
                else cout << res;
            }
        }
        cout << '\n';
    }
    return 0;
}