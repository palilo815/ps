#include <iostream>
using namespace std;

const int MAX = 2000001;

int fenwick[MAX];

void update(int i, int v) {
    while (i < MAX) {
        fenwick[i] += v;
        i += i & -i;
    }
}
int read(int i) {
    int ret = 0;
    while (i) {
        ret += fenwick[i];
        i -= i & -i;
    }
    return ret;
}
int query(int x) {
    int l = 0, r = MAX;
    while (l < r) {
        int m = (l + r) / 2;
        read(m) < x ? l = m + 1 : r = m;
    }
    update(l, -1);
    return l;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int Q; cin >> Q;
    while (Q--) {
        int q, x; cin >> q >> x;
        if (q == 1) update(x, 1);
        else cout << query(x) << '\n';
    }
    return 0;
}