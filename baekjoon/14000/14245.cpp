#include <bits/stdc++.h>
using namespace std;

const int max_N = 500001;

int N;
int fenwick[max_N];

void update(int i, int w) {
    for (++i; i <= N; i += i & -i)
        fenwick[i] ^= w;
}
int read(int i) {
    int ret = 0;
    for (++i; i; i -= i & -i)
        ret ^= fenwick[i];
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        int w; cin >> w;
        update(i, w);
        update(i + 1, w);
    }

    int Q; cin >> Q;
    while (Q--) {
        int q; cin >> q;
        if (q == 1) {
            int l, r, w; cin >> l >> r >> w;
            update(l, w);
            update(r + 1, w);
        }
        else {
            int i; cin >> i;
            cout << read(i) << '\n';
        }
    }
    return 0;
}