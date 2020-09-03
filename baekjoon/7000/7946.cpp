#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e6;

int a[mxN];

void solve() {
    int N, K; cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);
    cout << a[K - 1] << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}