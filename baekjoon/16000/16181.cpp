#include <bits/stdc++.h>
#define not_empty (!stk[top[u]].empty())
#define top_c stk[top[u]].back().c
#define top_s stk[top[u]].back().s
#define top_e stk[top[u]].back().e
#define pop stk[top[u]].pop_back()
using namespace std;

struct elem {
    int c, s, e;
    elem(int c, int s, int e) : c(c), s(s), e(e) {}
};

const int mxN = 2e5 + 1;

vector<int> adj[mxN];
int M = 1, sz[mxN], par[mxN], top[mxN], colour[mxN], cnt[mxN];
int* idx = sz;

vector<elem> stk[mxN];

void dfs(int u) {
    sz[u] = 1;
    for (int& v : adj[u]) {
        if (v == par[u]) continue;
        par[v] = u;
        dfs(v);
        sz[u] += sz[v];
        if (adj[u][0] == par[u] || sz[adj[u][0]] < sz[v])
            swap(v, adj[u][0]);
    }
}
void hld(int u) {
    if (adj[u].size() == 1) return;
    for_each(adj[u].begin() + 1, adj[u].end(), [&](int& v) {
        if (v == par[u]) return;
        top[v] = v, idx[v] = 1;
        hld(v);
    });

    int& h = adj[u][0];
    top[h] = top[u], idx[h] = idx[u] + 1;
    hld(h);
}
void query(int c, int u) {
    for (; u; u = par[top[u]]) {
        --cnt[colour[c]];
        ++cnt[colour[c] += idx[u] - (top[u] == 1)];
        for (; not_empty && top_e <= idx[u]; pop) {
            --cnt[colour[top_c]];
            ++cnt[colour[top_c] -= top_e - top_s];
        }
        if (not_empty) {
            --cnt[colour[top_c]];
            ++cnt[colour[top_c] -= idx[u] - top_s];
            top_s = idx[u];
        }
        stk[top[u]].emplace_back(c, top[u] == 1, idx[u]);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, C, Q;
    cin >> N >> C >> Q;

    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(1);

    adj[1].emplace_back(0);
    memset(idx + 1, 0, sizeof(int) * N);
    top[1] = 1, idx[1] = 1;

    hld(1);

    cnt[0] = C;

    for (int u, c, m; Q--;) {
        cin >> u >> c >> m;
        query(c, u);
        cout << cnt[m] << '\n';
    }
}