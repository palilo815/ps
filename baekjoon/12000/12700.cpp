#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<array<int, 2>> adj(n);
    for (auto& x : adj) {
        cin >> x[0] >> x[1];
    }
    vector<int> dep(n);
    auto dfs = [&](int root) {
        vector stk = {root};
        for (int i = n; i--;) {
            const auto u = stk.back();
            stk.pop_back();
            if (adj[u][0] > 0) {
                stk.emplace_back(adj[u][0] - 1);
                dep[adj[u][0] - 1] = dep[u] + 1;
            }
            if (adj[u][1] > 0) {
                stk.emplace_back(adj[u][1] - 1);
                dep[adj[u][1] - 1] = dep[u] + 1;
            }
        }
    };
    dfs(0);
    const auto max_dep = *max_element(dep.begin(), dep.end());
    vector<int> best(max_dep + 1);
    for (int u = 0; u < n; ++u) {
        if (adj[u][0] < 0) {
            chmax(best[dep[u]], -adj[u][0]);
        }
        if (adj[u][1] < 0) {
            chmax(best[dep[u]], -adj[u][1]);
        }
    }
    int s = 0, p = -1;
    for (int i = 0; i <= max_dep; ++i) {
        for (int new_s = best[i], diff = i - p; diff--;) {
            new_s <<= 1;
            if (new_s > s) {
                s = best[i], p = i;
                break;
            }
        }
    }
    string ans(p + 1, '0');
    for (int i = s; i; i >>= 1) {
        ans += '0' + (i & 1);
    }
    int num_zero = find(ans.begin(), ans.end(), '1') - ans.begin();
    reverse(ans.begin(), ans.end());
    ans.insert(ans.end(), max(0, max_dep - num_zero), '0');
    cout << ans;
}