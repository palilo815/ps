#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;

const int sgN = 524288;

int segT[sgN << 1];

void update(int i, int v) {
    for (i += sgN - 1; i; i >>= 1)
        segT[i] += v;
}
int query(int k) {
    int i = 1;
    while (i < sgN) {
        if (segT[left] < k) {
            k -= segT[left];
            i = right;
        }
        else i = left;
    }
    return i - sgN + 1;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = sgN; i < sgN + N; ++i)
        cin >> segT[i];

    for (int i = sgN - 1; i; --i)
        segT[i] = segT[left] + segT[right];

    int Q; cin >> Q;
    for (int q, i, v; Q; --Q) {
        cin >> q >> i;
        if (q == 1) {
            cin >> v;
            update(i, v);
        }
        else cout << query(i) << '\n';
    }
    return 0;
}