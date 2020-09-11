#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);

    for (int l, r; Q--;) {
        cin >> l >> r;
        cout << upper_bound(a, a + N, r) - lower_bound(a, a + N, l) << '\n';
    }
    return 0;
}