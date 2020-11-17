#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

const int mxN = 1e5;
const int sgN = 131072;

struct disjoint_set {
    vector<int> par, rank;
    vector<pair<int, int>> stk;

    void init(int n) {
        par = vector<int>(n, -1);
        rank = vector<int>(n);
    }
    int find(int u) {
        return ~par[u] ? find(par[u]) : u;
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (rank[u] < rank[v]) swap(u, v);
        par[v] = u;

        if (rank[u] == rank[v]) {
            ++rank[u];
            u = -u, v = -v;
        }
        stk.emplace_back(u, v);
    }
    void rollback(int checkpoint) {
        while (stk.size() != checkpoint) {
            auto [u, v] = stk.back();
            stk.pop_back();
            if (u < 0) {
                u = -u, v = -v;
                --rank[u];
            }
            par[v] = -1;
        }
    }
};

disjoint_set uf;
vector<p> segT[sgN << 1];
p query[mxN];
int t;

void add_edge(int l, int r, p edge) {
    for (l += sgN, r += sgN; l != r; l >>= 1, r >>= 1) {
        if (l & 1) segT[l++].emplace_back(edge);
        if (r & 1) segT[--r].emplace_back(edge);
    }
}
void solve(int l, int r, int i) {
    if (t <= l) return;

    int checkpoint = uf.stk.size();
    for (auto& [u, v] : segT[i])
        uf.merge(u, v);

    if (l + 1 == r) cout << (uf.find(query[l].first) == uf.find(query[l].second)) << '\n';
    else {
        int m = (l + r) >> 1;
        solve(l, m, i << 1);
        solve(m, r, i << 1 | 1);
    }
    uf.rollback(checkpoint);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    unordered_map<int64_t, int> mp;
    char op;

    for (int u, v; M--;) {
        cin >> op >> u >> v;
        if (u > v) swap(u, v);
        int64_t key = (int64_t)u << 32 | v;

        switch (op) {
        case '1': mp[key] = t; break;
        case '2':
            add_edge(mp[key], t, make_pair(u, v));
            mp.erase(key);
            break;
        default: query[t++] = {u, v};
        }
    }
    for (auto [key, s] : mp)
        add_edge(s, t, make_pair(key >> 32, key));

    uf.init(N + 1);

    solve(0, sgN, 1);
}