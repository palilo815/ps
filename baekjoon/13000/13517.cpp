#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct _query {
    int u, v, k;
};
struct BIT {
    int n, vt[mxN + 1];
    BIT(int n) : n(n) {}
    void reset() { memset(vt + 1, 0, sizeof(int) * n); }
    void update(int i) {
        for (++i; i <= n; i += i & -i)
            ++vt[i];
    }
    int query(int i) {
        int ret = 0;
        for (++i; i; i -= i & -i)
            ret += vt[i];
        return ret;
    }
};

vector<int> adj[mxN];
pair<int, int> a[mxN];
_query q[mxN];
int t, sz[mxN], par[mxN], top[mxN], in[mxN], lo[mxN], hi[mxN];

void dfs(int u) {
    sz[u] = 1;
    for (int& v : adj[u]) {
        if (v == par[u]) continue;
        par[v] = u;
        dfs(v);
        sz[u] += sz[v];
        if (adj[u][0] == par[u] || sz[v] > sz[adj[u][0]])
            swap(v, adj[u][0]);
    }
}
void hld(int u) {
    in[u] = t++;
    bool heavy = true;
    for (int& v : adj[u]) {
        if (v == par[u]) continue;
        top[v] = heavy ? top[u] : v;
        hld(v);
        heavy = false;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i].first, a[i].second = i;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> q[i].u >> q[i].v >> q[i].k;
        --q[i].u, --q[i].v;
    }

    sort(a, a + n, [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    dfs(0);
    hld(0);
    fill_n(hi, m, n);

    for (BIT bit(n);;) {
        vector<vector<int>> check(n);
        bool done = true;
        for (int i = 0; i < m; ++i)
            if (lo[i] != hi[i]) {
                check[lo[i] + hi[i] >> 1].emplace_back(i);
                done = false;
            }
        if (done) break;

        bit.reset();

        for (int mid = 0; mid < n; ++mid) {
            bit.update(in[a[mid].second]);
            for (int& i : check[mid]) {
                auto valid = [&]() {
                    int u = q[i].u, v = q[i].v, cnt = 0;
                    for (; top[u] != top[v]; u = par[top[u]]) {
                        if (sz[top[u]] > sz[top[v]]) swap(u, v);
                        if ((cnt += bit.query(in[u]) - bit.query(in[top[u]] - 1)) >= q[i].k)
                            return true;
                    }
                    if (in[u] > in[v]) swap(u, v);
                    return cnt + bit.query(in[v]) - bit.query(in[u] - 1) >= q[i].k;
                };
                valid() ? hi[i] = mid : lo[i] = mid + 1;
            }
        }
    }

    for (int i = 0; i < m; ++i)
        cout << a[lo[i]].first << '\n';
}