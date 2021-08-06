#include <bits/stdc++.h>
using namespace std;

struct kmp {
    int match(const string& s, const string& k) {
        const auto fail = lps(k);
        const int n = s.size(), m = k.size();
        int ret = 0;
        for (int i = 0, j = 0; i < n; ++i) {
            while (j && s[i] != k[j]) j = fail[j - 1];
            if (s[i] == k[j] && ++j == m) {
                ++ret;
                j = fail[m - 1];
            }
        }
        return ret;
    }

private:
    vector<int> lps(const string& s) {
        vector<int> vt(s.size());
        for (int i = 1, j = 0; i < int(s.size()); ++i) {
            while (j && s[i] != s[j]) j = vt[j - 1];
            if (s[i] == s[j]) vt[i] = ++j;
        }
        return vt;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    string k(n, 0), s(n << 1, 0);
    for (auto& c : k) {
        cin >> c;
    }
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    copy(s.begin(), s.begin() + n, s.begin() + n);
    auto ans = kmp().match(s, k) - equal(k.begin(), k.end(), s.begin());
    auto g = gcd(ans, n);
    cout << ans / g << '/' << n / g;
}