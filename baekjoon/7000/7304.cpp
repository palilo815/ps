#include <bits/stdc++.h>
using namespace std;

const int mx = 1000;

int w[mx];

void solve() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> w[i];
    sort(w, w + N, greater<int>());

    int ans = 0;
    for (int i = 0; i < N; ++i)
        ans = max(ans, w[i] * (i + 1));
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}