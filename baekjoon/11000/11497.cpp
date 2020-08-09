#include <bits/stdc++.h>
using namespace std;

const int mx = 1e4;

int a[mx], b[mx];

void solve() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    sort(a, a + N);

    for (int i = 0, l = 0, r = N; i < N - 1; i += 2)
        b[l++] = a[i], b[--r] = a[i + 1];
    if (N & 1) b[N / 2] = a[N - 1];

    int ans = b[N - 1] - b[0];
    for (int i = 0; i < N - 1; ++i)
        ans = max(ans, abs(b[i + 1] - b[i]));
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}