#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

class centroid_decomposition {
    const int n;
    vector<vector<int>> adj;
    vector<int> num;

public:
    centroid_decomposition(int _n) : n(_n), adj(n), num(n), sz(n), erased(n), book(n) {
        for (auto& x : num) {
            cin >> x, --x;
        }
        for (int i = n - 1, u, v; i--;) {
            cin >> u >> v, --u, --v;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
    }
    int get_ans() {
        solve(0);
        return ans;
    }

private:
    int s, time = 0, ans = INT_MAX;
    vector<int> sz;
    vector<bool> erased;
    vector<pair<int, int>> book;

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
    void dfs(int u, int p, int dep) {
        if (book[num[u]].first == time) {
            chmin(ans, dep + book[num[u]].second);
        }
        chmin(book[num[u]], pair(time, dep));
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v]) {
                dfs(v, u, dep + 1);
            }
        }
    }
    void solve(int u) {
        s = get_sz(u, -1);
        u = get_ct(u, -1);
        erased[u] = true;
        --time;
        for (const auto& v : adj[u]) {
            if (erased[v]) continue;
            dfs(v, u, 1);
        }
        if (book[num[u]].first == time) {
            chmin(ans, book[num[u]].second);
        }
        for (const auto& v : adj[u]) {
            if (!erased[v]) {
                solve(v);
            }
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
    cout << solver.get_ans();
}