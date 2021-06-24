#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

class _2_sat {
    int n;
    vector<vector<int>> adj;

public:
    _2_sat(int _n) : n(_n), adj(n << 1) {}

    void either(int x, int y) {
        x = x < 0 ? (~x << 1 | 1) : (x << 1);
        y = y < 0 ? (~y << 1 | 1) : (y << 1);
        assert(0 <= x and x < n << 1 and 0 <= y and y < n << 1);
        adj[x ^ 1].emplace_back(y);
        adj[y ^ 1].emplace_back(x);
    }
    void set_true(int x) { either(x, x); }
    void at_most_one(const vector<int>& v) {
        if (int(v.size()) < 2) return;
        int cur = ~v[0];
        for (int i = 2; i < int(v.size()); ++i) {
            int tmp = add_var();
            either(cur, ~v[i]);
            either(cur, tmp);
            either(~v[i], tmp);
            cur = ~tmp;
        }
        either(cur, ~v[1]);
    }
    vector<bool> solve() {
        dis.assign(n << 1, -1);
        low.assign(n << 1, 0);
        component_id.assign(n << 1, 0);

        for (int i = 0; i < (n << 1); ++i)
            if (dis[i] == -1)
                dfs(i);
        assert(stk.empty());

        vector<bool> ret(n);
        for (int i = 0; i < n; ++i) {
            if (component_id[i << 1] == component_id[i << 1 | 1])
                return {};
            ret[i] = component_id[i << 1] < component_id[i << 1 | 1];
        }
        return ret;
    }

private:
    vector<int> stk, dis, low, component_id;
    int dfs_time = 0, num_components = 0;

    int add_var() {
        adj.emplace_back();
        adj.emplace_back();
        return n++;
    }
    void dfs(int u) {
        low[u] = dis[u] = dfs_time++;
        stk.emplace_back(u);

        for (const auto& v : adj[u])
            if (dis[v] == -1) {
                dfs(v);
                chmin(low[u], low[v]);
            } else
                chmin(low[u], dis[v]);

        if (low[u] == dis[u]) {
            int x;
            do {
                x = stk.back();
                stk.pop_back();
                dis[x] = INT_MAX;
                component_id[x] = num_components;
            } while (x != u);
            ++num_components;
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int k, n;
    cin >> k >> n;

    // red -> true, blue -> false
    auto input = []() {
        int x;
        char c;
        cin >> x >> c;
        return c == 'R' ? x - 1 : -x;
    };

    _2_sat two_sat(k);
    for (int x, y, z; n--;) {
        x = input(), y = input(), z = input();
        two_sat.either(x, y);
        two_sat.either(y, z);
        two_sat.either(z, x);
    }

    auto ans = two_sat.solve();
    if (ans.empty()) return cout << -1, 0;

    for (const auto& x : ans)
        cout << (x ? 'R' : 'B');
}