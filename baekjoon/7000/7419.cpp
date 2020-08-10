#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4;

int N, K, a[mxN];

bool solve(double m) {
    int cnt = 0;
    for (int i = 0; i < N; ++i)
        cnt += (int)(a[i] / m);
    return cnt >= K;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> K;
    for (int i = 0; i < N; ++i) {
        double x; cin >> x;
        a[i] = x * 100;
    }

    int l = 0, r = 10000001, ans = 0;
    while (l ^ r) {
        int m = (l + r) / 2;
        solve(m) ? (l = m + 1, ans = m) : (r = m);
    }

    cout << ans / 100 << '.'
         << setfill('0') << setw(2) << ans % 100;
    return 0;
}