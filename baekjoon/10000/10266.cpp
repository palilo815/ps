#include <bits/stdc++.h>
using namespace std;

struct kmp {
    bool match(const vector<int>& s, const vector<int>& k) {
        const auto fail = lps(k);
        const int n = s.size(), m = k.size();
        for (int i = 0, j = 0; i < n; ++i) {
            while (j && s[i] != k[j]) j = fail[j - 1];
            if (s[i] == k[j] && ++j == m) {
                return true;
            }
        }
        return false;
    }

private:
    vector<int> lps(const vector<int>& s) {
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
    vector<int> a(n), b;
    b.reserve(n << 1);
    b.resize(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    {
        const int a_back = a.front() - a.back() + 360000;
        for (int i = 0; i < n - 1; ++i) {
            a[i] = a[i + 1] - a[i];
        }
        a.back() = a_back;
        const int b_back = b.front() - b.back() + 360000;
        for (int i = 0; i < n - 1; ++i) {
            b[i] = b[i + 1] - b[i];
        }
        b.back() = b_back;
        copy_n(b.begin(), n, back_inserter(b));
    }
    if (!kmp().match(b, a)) cout << "im";
    cout << "possible";
}