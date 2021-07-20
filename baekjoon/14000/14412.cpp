#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector adj(n, vector<bool>(n));
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u][v] = adj[v][u] = true;
    }
    vector<bool> flip(n);
    for (int i = 1; i < n; ++i) {
        flip[i] = !adj[i][0];
        bool ok = true;
        for (int j = 1; j < i; ++j) {
            if (!(adj[i][j] ^ flip[j] ^ flip[i])) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            break;
        }
        if (i == n - 1) {
            return cout << "DA", 0;
        }
    }
    fill(flip.begin(), flip.end(), false);
    flip[0] = true;
    for (int i = 1; i < n; ++i) {
        flip[i] = adj[i][0];
        bool ok = true;
        for (int j = 1; j < i; ++j) {
            if (!(adj[i][j] ^ flip[j] ^ flip[i])) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            break;
        }
        if (i == n - 1) {
            return cout << "DA", 0;
        }
    }
    cout << "NE";
}