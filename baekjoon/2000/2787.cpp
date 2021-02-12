#include <bits/stdc++.h>
using namespace std;

inline void chmin(int& a, int b) {
    if (a > b) a = b;
}
inline void chmax(int& a, int b) {
    if (a < b) a = b;
}

struct bipartite_matching {
    vector<vector<int>> adj;
    vector<int> match, rev;
    vector<bool> visited;
    int n, m;

    bipartite_matching(int n, int m) : n(n), m(m) {
        adj.resize(n), match.resize(n, -1), rev.resize(m, -1), visited.resize(n);
    }
    void add_edge(int u, int v) { adj[u].emplace_back(v); }
    bool dfs(int u) {
        visited[u] = true;
        for (const auto& v : adj[u]) {
            if (rev[v] == -1 || (!visited[rev[v]] && dfs(rev[v]))) {
                match[u] = v, rev[v] = u;
                return true;
            }
        }
        return false;
    }
    int maximum_matching() {
        for (bool update = true; update;) {
            fill(visited.begin(), visited.end(), false);
            update = false;

            for (int i = 0; i < n; ++i)
                if (match[i] == -1 && dfs(i))
                    update = true;
        }
        return n - count(match.begin(), match.end(), -1);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<int> lpos(n), rpos(n, n - 1), lval(n), rval(n, n - 1);
    for (int l, r, val; m--;) {
        char op;
        cin >> op >> l >> r >> val, --l, --r, --val;
        chmax(lpos[val], l);
        chmin(rpos[val], r);

        if (op == '1')
            for_each(rval.begin() + l, rval.begin() + r + 1, [&](auto& x) { chmin(x, val); });
        else
            for_each(lval.begin() + l, lval.begin() + r + 1, [&](auto& x) { chmax(x, val); });
    }

    bipartite_matching solver(n, n);
    for (int pos = 0; pos < n; ++pos)
        for (int val = lval[pos]; val <= rval[pos]; ++val)
            if (lpos[val] <= pos && pos <= rpos[val])
                solver.add_edge(pos, val);

    if (solver.maximum_matching() == n)
        for (int i = 0; i < n; ++i)
            cout << solver.match[i] + 1 << ' ';
    else
        cout << -1;
}