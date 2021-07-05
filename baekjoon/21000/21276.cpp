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
    map<string, int> table;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        table[a[i]] = i;
    }
    vector<vector<int>> adj(n);
    vector<int> in(n);
    vector is_root(n, true);
    int m;
    cin >> m;
    for (string v, u; m--;) {
        cin >> v >> u;
        adj[table[u]].emplace_back(table[v]);
        ++in[table[v]];
        is_root[table[v]] = false;
    }
    vector<vector<int>> kids(n);
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (!in[i]) {
            q.emplace(i);
        }
    }
    while (!q.empty()) {
        const auto u = q.front();
        q.pop();
        for (const auto& v : adj[u]) {
            if (--in[v] == 0) {
                kids[u].emplace_back(v);
                q.emplace(v);
            }
        }
    }
    vector<int> roots;
    for (int i = 0; i < n; ++i) {
        if (is_root[i]) {
            roots.emplace_back(i);
        }
    }
    sort(roots.begin(), roots.end(), [&](const auto& lhs, const auto& rhs) {
        return a[lhs] < a[rhs];
    });
    for (auto& vt : kids) {
        sort(vt.begin(), vt.end(), [&](const auto& lhs, const auto& rhs) {
            return a[lhs] < a[rhs];
        });
    }
    cout << roots.size() << '\n';
    for (const auto& root : roots) {
        cout << a[root] << ' ';
    }
    cout << '\n';
    for (const auto& [name, id] : table) {
        cout << name << ' ' << kids[id].size();
        for (const auto& kid : kids[id]) {
            cout << ' ' << a[kid];
        }
        cout << '\n';
    }
}