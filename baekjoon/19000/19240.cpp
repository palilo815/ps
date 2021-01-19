#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int u, v; m--;) {
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<char> colour(n);
    vector<int> stk;

    for (int i = 0; i < n; ++i) {
        if (colour[i]) continue;
        colour[i] = 'A';
        stk.emplace_back(i);
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();

            for (int& v : adj[u]) {
                if (!colour[v]) {
                    colour[v] = colour[u] == 'A' ? 'B' : 'A';
                    stk.emplace_back(v);
                } else if (colour[v] == colour[u]) {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }
    cout << "YES\n";
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}