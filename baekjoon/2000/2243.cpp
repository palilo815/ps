#include <bits/stdc++.h>
using namespace std;

int segT[1048576 * 2 - 1];
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
    --segT[idx];
    if (l == r) return l;
    int m = l + (r - l) / 2;
    if (segT[2 * idx + 1] >= k) return query(k, l, m, 2 * idx + 1);
    else return query(k - segT[2 * idx + 1], m + 1, r, 2 * idx + 2);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int Q; cin >> Q;
    while (Q--) {
        int q, a; cin >> q >> a;
        if (q == 1) cout << query(a, 0, 1000000, 0) << '\n';
        else {
            int b; cin >> b;
            update(a, b, 0, 1000000, 0);
        }
    }
    return 0;
}