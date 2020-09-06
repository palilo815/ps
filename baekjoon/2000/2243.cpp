#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;

const int sgN = 1048576;

int segT[sgN << 1];

void update(int i, int v) {
    for (i += sgN; i; i >>= 1)
        segT[i] += v;
}
int query(int k) {
    int i = 1;
    while (i < sgN) {
        --segT[i];
        if (segT[left] >= k) i = left;
        else {
            k -= segT[left];
            i = right;
        }
    }
    --segT[i];
    return i - sgN;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int Q; cin >> Q;
    for (int q, a, b; Q; --Q) {
        cin >> q >> a;
        if (q == 1) cout << query(a) << '\n';
        else {
            cin >> b;
            update(a, b);
        }
    }
    return 0;
}