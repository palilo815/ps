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
    int n;
    cin >> n;
    for (int u, v;;) {
        cin >> u >> v;
        if (u == -1) break;
        --u, --v;
        adj[u][v] = adj[v][u] = true;
    }
    for (int i = 0; i < n; ++i) {
        adj[i][i] = true;
    }
    vector<int> stk(n);
    vector<char> colour(n);
    for (int i = 0; i < n; ++i) {
        if (colour[i]) continue;
        colour[i] = 'b';
        stk[0] = i;
        for (int ptr = 1; ptr;) {
            const auto u = stk[--ptr];
            for (int v = 0; v < n; ++v) {
                if (adj[u][v]) continue;
                if (colour[v]) {
                    if (colour[u] == colour[v]) return cout << -1, 0;
                } else {
                    colour[v] = colour[u] == 'b' ? 'w' : 'b';
                    stk[ptr++] = v;
                }
            }
        }
    }
    cout << "1\n";
    for (const auto c : {'b', 'w'}) {
        for (int i = 0; i < n; ++i) {
            if (colour[i] == c) {
                cout << i + 1 << ' ';
            }
        }
        cout << "-1\n";
    }
}