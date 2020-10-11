#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

const int mxN = 1e6;
const int sgN = 1048576;

vector<int> adj[mxN];
int t, in[mxN], out[mxN];

int minT[sgN << 1], maxT[sgN << 1], lazy[sgN << 1];

void dfs(int u) {
    in[u] = t++;
    for (int& v : adj[u]) dfs(v);
    out[u] = t;
}
inline void prop(int i) {
    lazy[left] += lazy[i], lazy[right] += lazy[i];
    lazy[i] = 0;
}
inline void fix(int i) {
    minT[i] = min(minT[left] + lazy[left], minT[right] + lazy[right]);
    maxT[i] = max(maxT[left] + lazy[left], maxT[right] + lazy[right]);
}
pair<int, int> query(int l, int r, int ql, int qr, int i) {
    if (r <= ql || qr <= l) return {INT_MAX, INT_MIN};
    if (ql <= l && r <= qr) return {minT[i] + lazy[i], maxT[i] + lazy[i]};
    prop(i);

    int m = (l + r) >> 1;
    auto L = query(l, m, ql, qr, left), R = query(m, r, ql, qr, right);
    auto ret = make_pair(min(L.first, R.first), max(L.second, R.second));
    fix(i);
    return ret;
}
void update(int l, int r, int ql, int qr, int qv, int i) {
    if (r <= ql || qr <= l) return;
    if (ql <= l && r <= qr) {
        lazy[i] += qv;
        return;
    }
    prop(i);

    int m = (l + r) >> 1;
    update(l, m, ql, qr, qv, left), update(m, r, ql, qr, qv, right);
    fix(i);
}
void Q() {
    int i;
    cin >> i;
    --i;
    auto res = query(0, sgN, in[i], out[i], 1);
    cout << res.second - res.first << '\n';
}
void R() {
    int i, val;
    cin >> i >> val;
    --i;
    update(0, sgN, in[i], out[i], val, 1);
}
void solve() {
    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
        adj[i].clear();
    for (int v = 1, u; v < N; ++v) {
        cin >> u;
        adj[u - 1].emplace_back(v);
    }

    t = 0;
    dfs(0);

    for (int i = 0; i < N; ++i)
        cin >> minT[sgN + in[i]];
    move(minT + sgN, minT + sgN + N, maxT + sgN);
    memset(minT + sgN + N, 0x3f, sizeof(int) * (sgN - N));
    memset(maxT + sgN + N, 0x00, sizeof(int) * (sgN - N));

    for (int i = sgN - 1; i; --i) {
        minT[i] = min(minT[left], minT[right]);
        maxT[i] = max(maxT[left], maxT[right]);
    }

    memset(lazy, 0, sizeof(lazy));

    int M;
    cin >> M;

    for (char q; M--;) {
        cin >> q;
        q == 'Q' ? Q() : R();
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}