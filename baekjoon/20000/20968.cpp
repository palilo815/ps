#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (auto& x : a) cin >> x, --x;

    constexpr int mxK = 50;

    array<array<bool, mxK + 1>, mxK + 1> adj {};
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j) {
            char c;
            cin >> c;
            adj[i][j] = c == '1';
        }

    for (int i = 0; i < k; ++i)
        adj[i][k] = adj[i][a.back()];
    a.back() = k;

    vector<array<bool, mxK + 1>> visited(n);
    visited[0][a[0]] = true;

    deque<pair<int, int>> dq;
    dq.emplace_back(0, a[0]);
    dq.emplace_back(-1, -1);

    int ans = 0;
    for (;;) {
        const auto [i, u] = dq.front();
        dq.pop_front();

        if (i == -1) {
            if (dq.empty()) return cout << -1, 0;
            dq.emplace_back(-1, -1);
            ++ans;
            continue;
        }
        if (i == n - 1 && u == k) return cout << ans, 0;

        if (i && !visited[i - 1][u]) {
            visited[i - 1][u] = true;
            dq.emplace_back(i - 1, u);
        }
        if (i != n - 1 && !visited[i + 1][u]) {
            visited[i + 1][u] = true;
            dq.emplace_back(i + 1, u);
        }
        if (adj[u][a[i]] && !visited[i][a[i]]) {
            visited[i][a[i]] = true;
            dq.emplace_front(i, a[i]);
        }
    }
}