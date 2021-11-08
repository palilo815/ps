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
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> pref[i];
    }
    partial_sum(pref.begin(), pref.end(), pref.begin(), bit_xor());
    int ans = 0;
    for (int l, r; m--;) {
        cin >> l >> r, --l;
        ans ^= pref[l] ^ pref[r];
    }
    cout << ans;
}