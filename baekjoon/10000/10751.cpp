#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    string s;
    cin >> n >> s;
    vector<int> pref(n + 1), suff(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = s[i] == 'C';
    }
    for (int i = 0; i < n; ++i) {
        suff[i] = s[i] == 'W';
    }
    partial_sum(pref.begin(), pref.end(), pref.begin());
    partial_sum(suff.rbegin(), suff.rend(), suff.rbegin());
    int64_t ans = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'O') {
            ans += int64_t(pref[i]) * suff[i];
        }
    }
    cout << ans;
}