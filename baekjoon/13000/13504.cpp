#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct trie_node {
    int value;
    array<int, 2> child;
    trie_node() = default;
};

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<trie_node> trie(1);
    int node_count = 1;

    auto add = [&](int x) {
        int cur = 0;
        for (int i = 32; i--;) {
            int bit = x >> i & 1;
            if (!trie[cur].child[bit]) {
                trie[cur].child[bit] = node_count++;
                trie.emplace_back();
            }
            cur = trie[cur].child[bit];
        }
        trie[cur].value = x;
    };
    auto query = [&](int x) {
        int cur = 0;
        for (int i = 32; i--;) {
            int bit = x >> i & 1;
            if (trie[cur].child[!bit])
                cur = trie[cur].child[!bit];
            else if (trie[cur].child[bit])
                cur = trie[cur].child[bit];
            else
                break;
        }
        return x ^ trie[cur].value;
    };

    add(0);

    int ans = 0, xorsum = 0;
    for (const auto& x : a) {
        add(xorsum ^= x);
        chmax(ans, query(xorsum));
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}