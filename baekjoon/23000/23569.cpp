#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr size_t MX_N = 1e3;
    array<bitset<MX_N>, MX_N> adj {};
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        adj[i]._Unchecked_set(i);
    }
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u]._Unchecked_set(v);
        adj[v]._Unchecked_set(u);
    }
    vector<int> stk(n);
    vector<char> colour(n);
    auto split = [&](int s) -> int {
        int black = 1, white = 0;
        colour[s] = 'b';
        stk[0] = s;
        for (int ptr = 1; ptr;) {
            const auto u = stk[--ptr];
            for (int v = 0; v < n; ++v) {
                if (adj[u]._Unchecked_test(v)) continue;
                if (colour[v]) {
                    if (colour[u] == colour[v]) return -1;
                } else {
                    colour[v] = colour[u] == 'b' ? (++white, 'w') : (++black, 'b');
                    stk[ptr++] = v;
                }
            }
        }
        return abs(black - white);
    };
    bitset<2048> dp;
    dp._Unchecked_set(1024);
    for (int i = 0; i < n; ++i) {
        if (colour[i]) continue;
        const auto x = split(i);
        if (x == -1) return cout << -1, 0;
        dp = dp << x | dp >> x;
    }
    for (int i = 0;; ++i) {
        if (dp._Unchecked_test(1024 - i) || dp._Unchecked_test(1024 + i)) {
            return cout << i, 0;
        }
    }
}