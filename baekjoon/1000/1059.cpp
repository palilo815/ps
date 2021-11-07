#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    const auto mx = *max_element(a.begin(), a.end());
    cin >> n;
    int ans = 0;
    for (int l = 1; l <= n; ++l) {
        for (int r = n; r < mx; ++r) {
            if (l == r) continue;
            ans += none_of(a.begin(), a.end(), [&](const auto& x) {
                return l <= x && x <= r;
            });
        }
    }
    cout << ans;
}