#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> vt;
    vt.reserve(n * m + 1);
    for (int i = 1, x; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> x;
            vt.emplace_back(x, i * j);
        }
    vt.emplace_back(INT_MAX, 0); // sentinel

    sort(vt.begin(), vt.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    vector<bool> visited(n * m + 1);
    visited[n * m] = true;

    queue<int> q;
    q.emplace(n * m);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        auto it = lower_bound(vt.begin(), vt.end(), u, [&](const auto& val, const auto& key) {
            return val.first < key;
        });
        for (; it->first == u; ++it) {
            if (it->second == 1) return cout << "yes", 0;
            if (!visited[it->second]) {
                visited[it->second] = true;
                q.emplace(it->second);
            }
        }
    }
    cout << "no";
}