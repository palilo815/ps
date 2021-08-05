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
    vector<char> colour;
    vector<pair<int, int>> queries;
    vector<int> ans;

    using iter_t = vector<pair<int, int>>::iterator;

public:
    centroid_decomposition(int _n) : n(_n), adj(n), colour(n), sz(n), sub_root(n), dep(n), erased(n) {
        for (int i = n - 1, u, v; i--;) {
            cin >> u >> v, --u, --v;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
    }

    vector<int> get_ans() {
        int m;
        cin >> m;
        queries.resize(m);
        int print_query = 0;
        for (auto& [x, y] : queries) {
            char op;
            cin >> op >> y, --y;
            x = op == '1' ? -1 : print_query++;
        }
        ans.assign(print_query, INF);
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
        colour[u] = 0;
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v]) {
                dfs(v, u, root);
            }
        }
    }
    void solve(int u, iter_t st, iter_t ed) {
        s = get_sz(u, -1);
        u = get_ct(u, -1);
        erased[u] = true, colour[u] = 0, dep[u] = 0;
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
                    colour[it->second] ^= 1;
                    if (colour[it->second]) {
                        dists.emplace(dep[it->second]);
                    } else {
                        dists.erase(dists.find(dep[it->second]));
                    }
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
    int n;
    cin >> n;
    centroid_decomposition solver(n);
    const auto ans = solver.get_ans();
    for (const auto& x : ans) {
        cout << x << '\n';
    }
}