#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i {}, j; i < n; ++i) {
        auto ok {true};
        for (auto _ {n}; _--;) {
            cin >> j, --j;
            if (ok) adj[i].emplace_back(j);
            ok &= i != j;
        }
    }
    vector<int> stk;
    auto dfs = [&](int s, vector<int8_t>& visited) {
        stk.emplace_back(s);
        visited[s] = 1;
        while (!stk.empty()) {
            const auto u {stk.back()};
            stk.pop_back();
            for (const auto& v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = 1;
                    stk.emplace_back(v);
                }
            }
        }
    };
    vector visited(n, vector<int8_t>(n));
    for (int i {}; i < n; ++i) {
        dfs(i, visited[i]);
    }
    for (int u {}; u < n; ++u) {
        for (const auto& v : adj[u]) {
            if (visited[v][u]) {
                cout << v + 1 << '\n';
                break;
            }
        }
    }
}
