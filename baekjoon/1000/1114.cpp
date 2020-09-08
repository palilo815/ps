#include <bits/stdc++.h>
using namespace std;

const int mxK = 1e4;

int L, K, C, a[mxK + 1];

bool solve(int m) {
    for (int i = 0, cnt = 0, sum = 0; i < K; ++i) {
        if (sum + a[i] > m) {
            if (++cnt > C) return false;
            sum = 0;
        }
        sum += a[i];
    }
    return true;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> L >> K >> C;
    for (int i = 0; i < K; ++i)
        cin >> a[i];

    sort(a, a + K);
    a[K++] = L;
    adjacent_difference(a, a + K, a);

    int l = *max_element(a, a + K), r = L;
    while (l ^ r) {
        int m = (l + r) >> 1;
        solve(m) ? (r = m) : (l = m + 1);
    }

    int fst = 0, cnt = 0;
    for (int i = K - 1, sum = 0; ~i; --i) {
        if (sum + a[i] > l)
            sum = 0, ++cnt, fst = i;
        sum += a[i];
    }
    cout << l << ' ' << (cnt == C ? accumulate(a, a + fst + 1, 0) : a[0]);
    return 0;
}