#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto ans = accumulate(a.begin(), a.begin() + m, 0),
         cur = ans,
         cnt = 1;
    for (int i = 0; i + m < n; ++i) {
        cur += a[i + m] - a[i];
        if (cur > ans) {
            ans = cur, cnt = 1;
        } else if (cur == ans) {
            ++cnt;
        }
    }
    if (ans == 0) {
        cout << "SAD";
    } else {
        cout << ans << ' ' << cnt;
    }
}