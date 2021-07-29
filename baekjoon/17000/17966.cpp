#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (auto& x : adj) {
        x.reserve(n - 1);
    }
    for (int i = n * (n - 1) / 2, u, v, w; i--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w);
        adj[v].emplace_back(w);
    }
    int64_t ans = 0;
    for (auto& x : adj) {
        sort(x.begin(), x.end(), greater());
        for (int i = 0; i < n - 1; i += 2) {
            ans += x[i];
        }
    }
    cout << ans;
}