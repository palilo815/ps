#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e2;

vector<int> adj[mxN];
bitset<mxN> visited;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 1, u, v; i < n; ++i) {
        cin >> v >> u;
        adj[u - 1].emplace_back(v - 1);
    }

    for (int i = 0; i < n; ++i) {
        visited.reset();
        visited[i] = true;
        vector<int> stk = {i};
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();

            for (int& v : adj[u])
                if (!visited[v]) {
                    visited[v] = true;
                    stk.emplace_back(v);
                }
        }
        if (visited.count() == n) return cout << i + 1, 0;
    }
    cout << -1;
}