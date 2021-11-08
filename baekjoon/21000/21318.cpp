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
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> pref[i];
    }
    for (int i = 1; i < n; ++i) {
        pref[i] = pref[i] > pref[i + 1];
    }
    pref[n] = 0;
    partial_sum(pref.begin(), pref.end(), pref.begin());
    cin >> n;
    for (int l, r; n--;) {
        cin >> l >> r, --l, --r;
        cout << pref[r] - pref[l] << '\n';
    }
}