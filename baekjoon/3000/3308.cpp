#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> s(m), k(n);
    for (auto& x : k) cin >> x, --x;
    for (auto& x : s) cin >> x;
    const auto [l, r] {[&]() {
        const auto value {k};
        vector<int> pre(n), nxt(n);
        for (int i {}; i < n; ++i) {
            k[value[i]] = i;
        }
        iota(pre.begin(), pre.end(), -1);
        iota(nxt.begin(), nxt.end(), 1);
        vector<int> l(n), r(n);
        for (auto i {n}; i--;) {
            if (pre[k[i]] != -1) {
                l[i] = i - value[pre[k[i]]];
                nxt[pre[k[i]]] = nxt[k[i]];
            }
            if (nxt[k[i]] != n) {
                r[i] = i - value[nxt[k[i]]];
                pre[nxt[k[i]]] = pre[k[i]];
            }
        }
        return make_pair(l, r);
    }()};
    vector<int> pi(n);
    for (int i {1}, j {}; i < n; ++i) {
        while (j && (k[i] < k[i - l[j]] || k[i] > k[i - r[j]])) j = pi[j - 1];
        if (!(k[i] < k[i - l[j]] || k[i] > k[i - r[j]])) pi[i] = ++j;
    }
    vector<int> ans;
    for (int i {}, j {}; i < m; ++i) {
        while (j && (s[i] < s[i - l[j]] || s[i] > s[i - r[j]])) j = pi[j - 1];
        if (!(s[i] < s[i - l[j]] || s[i] > s[i - r[j]]) && ++j == n) {
            ans.emplace_back(i - n + 2);
            j = pi[j - 1];
        }
    }
    cout << ans.size() << '\n';
    for (const auto& x : ans) {
        cout << x << ' ';
    }
}
