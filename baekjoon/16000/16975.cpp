#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_N = 100000;

int N;
ll fenwick[max_N + 1];

void update(int idx, int val) {
    while (idx <= N) {
        fenwick[idx] += val;
        idx += (idx & -idx);
    }
}
ll read(int idx) {
    ll ret = 0;
    while (idx) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int x; cin >> x;
        update(i, x);
        update(i + 1, -x);
    }

    int Q; cin >> Q;
    while (Q--) {
        int q; cin >> q;
        if (q == 1) {
            int ql, qr, qv; cin >> ql >> qr >> qv;
            update(ql, qv);
            update(qr + 1, -qv);
        }
        else {
            int qi; cin >> qi;
            cout << read(qi) << '\n';
        }
    }
    return 0;
}