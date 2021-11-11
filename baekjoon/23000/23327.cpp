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
    vector<int64_t> pref(n + 1), pref2(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> pref[i];
    }
    partial_sum(pref.begin(), pref.end(), pref2.begin(), [&](const auto& sum, const auto& x) {
        return sum + x * x;
    });
    partial_sum(pref.begin(), pref.end(), pref.begin());
    for (int l, r; m--;) {
        cin >> l >> r, --l;
        cout << ((pref[r] - pref[l]) * (pref[r] - pref[l]) - (pref2[r] - pref2[l])) / 2 << '\n';
    }
}