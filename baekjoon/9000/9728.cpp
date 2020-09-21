#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e4;

int a[mxN];

int solve() {
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    int ret = 0;
    for (int i = 0, j = N - 1; i < j;) {
        if (a[i] + a[j] == K) ++ret;
        a[i] + a[j] < K ? ++i : --j;
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
        cout << "Case #" << t << ": " << solve() << '\n';
    return 0;
}