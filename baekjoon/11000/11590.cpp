#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<map<pair<char, char>, int>> trie(1);
    vector<int> dp(1);
    int node_count = 1, ans = 0;

    auto add = [&](string& s) {
        int cur = 0, mx = 0;
        for (int i = 0, m = s.size(); i < m; ++i) {
            pair key = {s[i], s[m - 1 - i]};
            if (!trie[cur][key]) {
                trie[cur][key] = node_count++;
                trie.emplace_back();
                dp.emplace_back();
            }
            cur = trie[cur][key];
            chmax(mx, dp[cur] + 1);
        }
        chmax(ans, dp[cur] = mx);
    };

    for (string s; n--;) {
        cin >> s;
        add(s);
    }
    cout << ans;
}