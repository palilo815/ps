#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    partial_sum(a, a + N, a);

    for (int l, m, r, q; Q--;) {
        cin >> q;
        for (l = 0, r = N; l ^ r;) {
            m = (l + r) >> 1;
            a[m] > q ? (r = m) : (l = m + 1);
        }
        cout << l + 1 << '\n';
    }
    return 0;
}