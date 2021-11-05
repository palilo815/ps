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
    vector<int> nxt(n);
    for (auto& x : nxt) {
        cin >> x, --x;
    }
    vector<int> indeg(n);
    for (const auto& x : nxt) {
        ++indeg[x];
    }
    vector<int> ans;
    const auto dfs = [&](int u) {
        for (;; u = nxt[u]) {
            ans.emplace_back(u);
            if (indeg[u] == -1) break;
            indeg[u] = -1;
        }
    };
    dfs(0);
    ans.erase(ans.begin());
    for (int i = 1; i < n; ++i) {
        if (!indeg[i]) {
            dfs(i);
        }
    }
    for (int i = 1; i < n; ++i) {
        if (~indeg[i]) {
            dfs(i);
        }
    }
    cout << ans.size() << '\n';
    for (const auto& x : ans) {
        cout << x + 1 << ' ';
    }
}