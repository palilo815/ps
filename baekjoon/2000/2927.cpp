#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 30001;
const int max_Q = 300001;

vector<int> adj[max_N];
int N, pen[max_N], qu[max_Q], qv[max_Q];
char qq[max_Q];

int t, sz[max_N], par[max_N], top[max_N], idx[max_N];
int fenwick[max_N];

int parent[max_N];

int _find(int u) {
    if (parent[u] < 0) return u;
    return parent[u] = _find(parent[u]);
}
void _union(int u, int v) {
    int U = _find(u), V = _find(v);
    if (U ^ V) {
        parent[U] = V;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
}
int dfs(int u, int p) {
    for (int& v : adj[u])
        if (v ^ p)
            sz[u] += dfs(v, u);
    return ++sz[u];
}
void hld(int u, int p) {
    int H = 0;
    for (int& v : adj[u])
        if (v ^ p && sz[v] > sz[H])
            H = v;
    for (int& v : adj[u])
        if (v ^ p && v ^ H)
            hld(v, u);

    if (!top[u]) top[u] = u;
    if (H) top[H] = top[u], hld(H, u);

    par[u] = p, idx[u] = ++t;
}
void update(int i, int v) {
    for (; i <= N; i += i & -i)
        fenwick[i] += v;
}
int read(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int query(int u, int v) {
    int ret = 0;
    while (top[u] ^ top[v]) {
        int& n = sz[top[u]] < sz[top[v]] ? u : v;
        ret += read(idx[top[n]]) - read(idx[n] - 1);
        n = par[top[n]];
    }
    if (idx[u] > idx[v]) swap(u, v);
    ret += read(idx[v]) - read(idx[u] - 1);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    LOOP(i, N) cin >> pen[i];
    int Q; cin >> Q;
    LOOP(i, Q) {
        string q; cin >> q >> qu[i] >> qv[i];
        qq[i] = q[0];
    }

    memset(parent + 1, -1, sizeof(int) * N);
    LOOP(i, Q) if (qq[i] == 'b')
        _union(qu[i], qv[i]);

    LOOP(i, N) if (!sz[i])
        dfs(i, 0);
    LOOP(i, N) if (!idx[i])
        hld(i, 0);

    LOOP(i, N) update(idx[i], pen[i]);
    memset(parent + 1, -1, sizeof(int) * N);

    for (int i = 1, u, v, x; i <= Q; ++i) switch (qq[i]) {
        case 'b':
            u = _find(qu[i]), v = _find(qv[i]);
            if (u == v) cout << "no\n";
            else {
                cout << "yes\n";
                parent[u] = v;
            }
            break;
        case 'e':
            u = _find(qu[i]), v = _find(qv[i]);
            if (u == v) cout << query(qu[i], qv[i]) << '\n';
            else cout << "impossible\n";
            break;
        default:
            u = qu[i], v = qv[i];
            x = v - pen[u];
            pen[u] = v;
            update(idx[u], x);
        }
    return 0;
}