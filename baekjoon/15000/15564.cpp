#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

constexpr int INF = 0x3f3f3f3f;

class centroid_decomposition {
    const int n;
    vector<vector<int>> adj;
    vector<pair<int, int>> queries;
    vector<int> ans;

    using iter_t = vector<pair<int, int>>::iterator;

public:
    centroid_decomposition(int _n, int _m) : n(_n), adj(n), sz(n), sub_root(n), dep(n), erased(n), queries(_m) {
        for (int u = 1, v; u < n; ++u) {
            cin >> v, --v;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
        int print_query = 0;
        for (auto& [x, y] : queries) {
            cin >> x >> y, --y;
            x = x == 1 ? -1 : print_query++;
        }
        ans.assign(print_query, INF);
    }

    vector<int> get_ans() {
        solve(0, queries.begin(), queries.end());
        replace(ans.begin(), ans.end(), INF, -1);
        return move(ans);
    }

private:
    int s;
    vector<int> sz, sub_root, dep;
    vector<bool> erased;

    int get_sz(int u, int p) {
        sz[u] = 1;
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v]) {
                sz[u] += get_sz(v, u);
            }
        }
        return sz[u];
    }
    int get_ct(int u, int p) const {
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v] && sz[v] > s / 2) {
                return get_ct(v, u);
            }
        }
        return u;
    }
    void dfs(int u, int p, int root) {
        sub_root[u] = root;
        dep[u] = dep[p] + 1;
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v]) {
                dfs(v, u, root);
            }
        }
    }
    void solve(int u, iter_t st, iter_t ed) {
        s = get_sz(u, -1);
        u = get_ct(u, -1);
        erased[u] = true, dep[u] = 0;
        for (const auto& v : adj[u]) {
            if (!erased[v]) {
                dfs(v, u, v);
            }
        }
        {
            multiset<int> dists;
            for (auto it = st; it != ed; ++it) {
                if (it->first == -1) {
                    // update
                    dists.emplace(dep[it->second]);
                } else if (!dists.empty()) {
                    // print
                    chmin(ans[it->first], dep[it->second] + *dists.begin());
                }
            }
        }
        ed = remove_if(st, ed, [&](const auto& x) {
            return x.second == u;
        });
        stable_sort(st, ed, [&](const auto& lhs, const auto& rhs) {
            return sub_root[lhs.second] < sub_root[rhs.second];
        });
        for (auto it = st; it != ed;) {
            auto it0 = it++;
            while (it != ed && sub_root[it0->second] == sub_root[it->second]) {
                ++it;
            }
            solve(sub_root[it0->second], it0, it);
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    centroid_decomposition solver(n, m);
    const auto ans = solver.get_ans();
    for (const auto& x : ans) {
        cout << x << '\n';
    }
}