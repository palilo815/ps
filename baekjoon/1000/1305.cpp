#include <bits/stdc++.h>
using namespace std;

struct kmp {
    vector<int> match(const string& s, const string& k) {
        const auto fail = lps(k);
        const int n = s.size(), m = k.size();

        vector<int> ret;
        for (int i = 0, j = 0; i < n; ++i) {
            while (j && s[i] != k[j]) j = fail[j - 1];
            if (s[i] == k[j] && ++j == m) {
                ret.emplace_back(i - m + 1);
                j = fail[m - 1];
            }
        }
        return ret;
    }
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
    string s;
    cin >> n >> s;
    cout << n - kmp().lps(s).back();
}