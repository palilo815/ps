#include <bits/stdc++.h>

struct Node {
    std::array<int, 26> next;
    int cnt;
};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<Node> trie(1);
    for (char s[301]; n--;) {
        cin >> s;
        for (auto i = 0, cur = 0; s[i]; ++i) {
            auto const c = s[i] - 'a';
            if (!trie[cur].next[c]) {
                trie[cur].next[c] = trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].next[c];
            ++trie[cur].cnt;
        }
    }
    string s;
    cin >> s;
    vector<int> dp(s.size() + 1);
    dp[0] = 1;
    constexpr int64_t MOD = 1'000'000'007;
    for (auto i = 0; i < static_cast<int>(s.size()); ++i) {
        auto const acc = static_cast<int64_t>(dp[i]);
        auto cur = 0;
        for (auto j = i; j < static_cast<int>(s.size()); ++j) {
            auto const c = s[j] - 'a';
            if (!trie[cur].next[c]) break;
            cur = trie[cur].next[c];
            dp[j + 1] = (dp[j + 1] + acc * trie[cur].cnt) % MOD;
        }
    }
    cout << dp.back();
}
