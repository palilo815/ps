#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    vector<array<int, 3>> pref(s.size() + 1);
    for (auto i {0}; i < static_cast<int>(s.size()); ++i) {
        pref[i + 1] = pref[i];
        if (s[i] == 'C') ++pref[i + 1][0];
        if (s[i] == 'O') ++pref[i + 1][1];
        if (s[i] == 'W') ++pref[i + 1][2];
    }
    int q;
    cin >> q;
    for (int l, r; q--;) {
        cin >> l >> r, --l;
        const auto c {(pref[r][0] - pref[l][0]) & 1};
        const auto o {(pref[r][1] - pref[l][1]) & 1};
        const auto w {(pref[r][2] - pref[l][2]) & 1};
        cout << ((c && !o && !w) || (!c && o && w) ? 'Y' : 'N');
    }
}
