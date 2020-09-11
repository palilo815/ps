#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int N, M, a[mxN];

bool solve(int m) {
    for (int cnt = 1, s = 0, i = 0; i < N; ++i) {
        if (s + a[i] > m) {
            if (++cnt > M) return false;
            s = 0;
        }
        s += a[i];
    }
    return true;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    int l = *max_element(a, a + N);
    int r = accumulate(a, a + N, 0);
    while (l ^ r) {
        int m = (l + r) >> 1;
        solve(m) ? (r = m) : (l = m + 1);
    }
    cout << l;
    return 0;
}