#include <bits/stdc++.h>
using namespace std;

void solve() {
    int L, N; cin >> L >> N;
    int mn = 0, mx = 0;
    for (int x; N--;) {
        cin >> x;
        if (L - x < x) x = L - x;
        mn = max(mn, x);
        mx = max(mx, L - x);
    }
    cout << mn << ' ' << mx << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}