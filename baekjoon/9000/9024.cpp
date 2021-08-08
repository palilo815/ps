#include <bits/stdc++.h>
using namespace std;

constexpr int MX_N = 1e6;

int a[MX_N];

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a, a + n);
    int best = INT_MAX, cnt = 0;
    for (int i = 0, j = n - 1; i != j;) {
        const int diff = abs(a[i] + a[j] - k);
        if (diff < best) {
            best = diff;
            cnt = 1;
        } else if (diff == best) {
            ++cnt;
        }
        a[i] + a[j] < k ? ++i : --j;
    }
    cout << cnt << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}