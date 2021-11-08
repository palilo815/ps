#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    const auto bfs = [&](const int s, const int t) {
        queue<pair<int, int>> q;
        q.emplace(s, t);
        set<pair<int, int>> visited;
        for (int ans = 0;; ++ans) {
            for (int sz = q.size(); sz--;) {
                const auto [u, v] = q.front();
                q.pop();
                if (u == v) return ans;
                if (u * 2 <= v + 3 && !visited.count({u * 2, v + 3})) {
                    visited.emplace(u * 2, v + 3);
                    q.emplace(u * 2, v + 3);
                }
                if (!visited.count({u + 1, v})) {
                    visited.emplace(u + 1, v);
                    q.emplace(u + 1, v);
                }
            }
        }
        return -1;
    };
    int tc;
    cin >> tc;
    for (int s, t; tc--;) {
        cin >> s >> t;
        cout << bfs(s, t) << '\n';
    }
}