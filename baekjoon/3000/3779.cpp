#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    auto get_lps = [&](string& s) {
        vector<int> lps(s.size());
        for (int i = 1, j = 0; i < int(lps.size()); ++i) {
            while (j && s[i] != s[j]) j = lps[j - 1];
            if (s[i] == s[j]) lps[i] = ++j;
        }
        return lps;
    };

    string s;
    for (int t = 1, n;; ++t) {
        cin >> n;
        if (!n) break;
        cin >> s;

        auto lps = get_lps(s);

        cout << "Test case #" << t << '\n';
        for (int i = 0; i < n; ++i)
            if (lps[i])
                if (int idx = gcd(i + 1, lps[i]); i + 1 == lps[i] + idx)
                    cout << i + 1 << ' ' << (i + 1) / idx << '\n';
        cout << '\n';
    }
}