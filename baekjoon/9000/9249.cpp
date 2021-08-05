#include <bits/stdc++.h>
using namespace std;

struct suffix_array {
    vector<int> sa, lcp;
    suffix_array(const string& s, int lim = 256) {
        int n = s.size() + 1, k = 0;
        vector<int> x(s.begin(), s.end() + 1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y;
        iota(sa.begin(), sa.end(), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j;
            iota(y.begin(), y.end(), n - j);
            for (int i = 0; i < n; ++i) {
                if (sa[i] >= j) {
                    y[p++] = sa[i] - j;
                }
            }
            fill(ws.begin(), ws.end(), 0);
            for (int i = 0; i < n; ++i) {
                ++ws[x[i]];
            }
            for (int i = 1; i < lim; ++i) {
                ws[i] += ws[i - 1];
            }
            for (int i = n; i--;) {
                sa[--ws[x[y[i]]]] = y[i];
            }
            swap(x, y);
            p = 1, x[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                const auto a = sa[i - 1], b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
        }
        for (int i = 1; i < n; ++i) {
            rank[sa[i]] = i;
        }
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k) {
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++) {
                ;
            }
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s, t;
    cin >> s >> t;
    suffix_array sa(s + "#" + t);
    int ans = 0;
    for (int i = 1; i < int(sa.lcp.size()); ++i) {
        if ((sa.sa[i] < int(s.size())) ^ (sa.sa[i - 1] < int(s.size())) && sa.lcp[ans] < sa.lcp[i]) {
            ans = i;
        }
    }
    const auto len = sa.lcp[ans];
    if (!(sa.sa[ans] < int(s.size()))) --ans;
    cout << len << '\n';
    cout << string(s.begin() + sa.sa[ans], s.begin() + sa.sa[ans] + len);
}