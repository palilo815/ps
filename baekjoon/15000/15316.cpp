#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

const int mxN = 2e5;
const int sgN = 262144;

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
vector<int> segT[sgN << 1];
p edge[mxN], query[mxN];
int t, mp[mxN];

void add_edge(int l, int r, int i) {
    for (l += sgN, r += sgN; l != r; l >>= 1, r >>= 1) {
        if (l & 1) segT[l++].emplace_back(i);
        if (r & 1) segT[--r].emplace_back(i);
    }
}
void solve(int l, int r, int i) {
    if (t <= l) return;

    int checkpoint = uf.stk.size();
    for (auto& x : segT[i])
        uf.merge(edge[x].first, edge[x].second);

    if (l + 1 == r) cout << (uf.find(query[l].first) == uf.find(query[l].second) ? "YES\n" : "NO\n");
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

    for (int i = 0; i < M; ++i)
        cin >> edge[i].first >> edge[i].second;

    for (int i = 0, x; i < M; ++i) {
        cin >> x;
        if (!x) mp[i] = -1;
    }

    int Q;
    cin >> Q;

    char op;
    for (int i; Q--;) {
        cin >> op;
        if (op == '2') {
            cin >> query[t].first >> query[t].second;
            ++t;
        } else {
            cin >> i;
            --i;
            if (mp[i] == -1) mp[i] = t;
            else {
                add_edge(mp[i], t, i);
                mp[i] = -1;
            }
        }
    }
    for (int i = 0; i < M; ++i)
        if (~mp[i])
            add_edge(mp[i], t, i);

    uf.init(N + 1);

    solve(0, sgN, 1);
}