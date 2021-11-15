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
    array<array<bool, MX_N>, MX_N> adj {};
    int n, m;
    cin >> n >> m;
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u][v] = adj[v][u] = true;
    }
    for (int i = 0; i < n; ++i) {
        adj[i][i] = true;
    }
    vector<int> stk(n);
    vector<char> colour(n);
    int alone = 0;
    auto split = [&](int s) -> int {
        int black = 1, white = 0;
        colour[s] = 'b';
        stk[0] = s;
        for (int ptr = 1; ptr;) {
            const auto u = stk[--ptr];
            for (int v = 0; v < n; ++v) {
                if (adj[u][v]) continue;
                if (colour[v]) {
                    if (colour[u] == colour[v]) return -1;
                } else {
                    colour[v] = colour[u] == 'b' ? (++white, 'w') : (++black, 'b');
                    stk[ptr++] = v;
                }
            }
        }
        if (black == 1 && white == 0) ++alone, --black;
        return abs(black - white);
    };
    vector<int> item;
    for (int i = 0; i < n; ++i) {
        if (colour[i]) continue;
        auto res = split(i);
        if (res == -1) return cout << -1, 0;
        if (res) item.emplace_back(res);
    }
    bitset<1024> dp;
    dp._Unchecked_set(0);
    for (const auto& x : item) {
        dp = dp << x | dp >> x;
    }
    int ans = INT_MAX;
    for (int i = 0; i <= n; ++i) {
        if (dp._Unchecked_test(i)) {
            chmin(ans, i < alone ? ((alone - i) & 1) : i - alone);
        }
    }
    cout << ans;
}