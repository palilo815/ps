#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
#define m ((l+r)>>1)
using namespace std;

const uint max_N = 5e5 + 1;
const uint seg_N = 524288;

vector<uint> adj[max_N];
uint t, par[max_N], sz[max_N], in[max_N], top[max_N];

uint segT[seg_N << 1], a[seg_N << 1], b[seg_N << 1];

void dfs(uint u, uint p) {
    sz[u] = 1, par[u] = p;
    for (uint& v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[adj[u][0]])
            swap(v, adj[u][0]);
    }
}
void hld(uint u, uint p) {
    in[u] = t++;
    for (uint& v : adj[u]) {
        if (v == p) continue;
        top[v] = (v == adj[u][0] ? top[u] : v);
        hld(v, u);
    }
}
uint sum(uint i, uint k) {
    return a[i] * segT[i] + b[i] * k;
}
void prop(uint i, uint k) {
    segT[i] = sum(i, k);
    if (k ^ 1) {
        a[left] *= a[i], b[left] = a[i] * b[left] + b[i];
        a[right] *= a[i], b[right] = a[i] * b[right] + b[i];
    }
    a[i] = 1, b[i] = 0;
}
void update(uint l, uint r, uint ql, uint qr, uint qa, uint qb, uint i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        a[i] *= qa, b[i] = b[i] * qa + qb;
        return;
    }
    if (a[i] ^ 1 || b[i]) prop(i, r - l);

    update(l, m, ql, qr, qa, qb, left), update(m, r, ql, qr, qa, qb, right);
    segT[i] = sum(left, (r - l) >> 1) + sum(right, (r - l) >> 1);
}
uint query(uint l, uint r, uint ql, uint qr, uint i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return sum(i, r - l);
    if (a[i] ^ 1 || b[i]) prop(i, r - l);

    return query(l, m, ql, qr, left) + query(m, r, ql, qr, right);
}
void u_hld(uint u, uint v, uint qa, uint qb) {
    while (top[u] ^ top[v]) {
        uint& n = sz[top[u]] < sz[top[v]] ? u : v;
        update(0, seg_N, in[top[n]], in[n] + 1, qa, qb, 1);
        n = par[top[n]];
    }
    if (in[u] > in[v]) swap(u, v);
    update(0, seg_N, in[u], in[v] + 1, qa, qb, 1);
}
uint q_hld(uint u, uint v) {
    uint ret = 0;
    while (top[u] ^ top[v]) {
        uint& n = sz[top[u]] < sz[top[v]] ? u : v;
        ret += query(0, seg_N, in[top[n]], in[n] + 1, 1);
        n = par[top[n]];
    }
    if (in[u] > in[v]) swap(u, v);
    ret += query(0, seg_N, in[u], in[v] + 1, 1);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    uint N, M; cin >> N >> M;
    for (uint i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    top[1] = 1;

    dfs(1, 0);
    hld(1, 0);
    fill_n(a, seg_N + N, 1);

    for (uint i = 0, q, l, r, v; i < M; ++i) {
        cin >> q;
        if (q & 1) {
            cin >> l;
            r = in[l] + sz[l]; l = in[l];
            if (q == 5) cout << query(0, seg_N, l, r, 1) << '\n';
            else {
                cin >> v;
                q == 1 ? update(0, seg_N, l, r, 1, v, 1) : update(0, seg_N, l, r, v, 0, 1);
            }
        }
        else {
            cin >> l >> r;
            if (q == 6) cout << q_hld(l, r) << '\n';
            else {
                cin >> v;
                q == 2 ? u_hld(l, r, 1, v) : u_hld(l, r, v, 0);
            }
        }
    }
    return 0;
}