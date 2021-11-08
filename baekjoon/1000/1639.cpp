#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    cin >> s;
    vector<int> pref(s.size() + 1);
    for (int i = 0; i < int(s.size()); ++i) {
        pref[i + 1] = s[i] - '0';
    }
    partial_sum(pref.begin(), pref.end(), pref.begin());
    int l = s.size() / 2;
    for (; l; --l) {
        for (int i = 0; i + l + l <= int(s.size()); ++i) {
            if (pref[i + l] - pref[i] == pref[i + l + l] - pref[i + l]) {
                return cout << l * 2, 0;
            }
        }
    }
    cout << 0;
}