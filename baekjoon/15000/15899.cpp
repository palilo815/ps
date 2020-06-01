#include <bits/stdc++.h>
using namespace std;
typedef vector<int> VI;

const int max_N = 200001;
const int mod = 1000000007;

VI adj[max_N];
VI segT[262144 * 2 - 1];
int colour[max_N];
int recolour[max_N];
int _time;
int in[max_N];
int out[max_N];

void DFS(int u, int p) {
    in[u] = ++_time;
    for (int v : adj[u]) if (v != p)
        DFS(v, u);
    out[u] = _time;
}
VI merge_segT(VI& a, VI& b) {
    size_t A = a.size(), B = b.size();
    VI ret;
    ret.reserve(A + B);

    size_t i = 0, j = 0;
    while (i < A && j < B) {
        if (a[i] < b[j]) ret.emplace_back(a[i++]);
        else ret.emplace_back(b[j++]);
    }
    while (i < A) ret.emplace_back(a[i++]);
    while (j < B) ret.emplace_back(b[j++]);
    return ret;
}
void build_segT(int l, int r, int i) {
    if (l == r) {
        segT[i].emplace_back(recolour[l]);
        return;
    }

    int m = (l + r) >> 1;
    build_segT(l, m, 2 * i + 1);
    build_segT(m + 1, r, 2 * i + 2);
    segT[i] = merge_segT(segT[2 * i + 1], segT[2 * i + 2]);
}
int query(int ql, int qr, int qv, int l, int r, int i) {
    if (ql <= l && r <= qr)
        return upper_bound(segT[i].begin(), segT[i].end(), qv) - segT[i].begin();
    if (qr < l || r < ql) return 0;

    int m = (l + r) >> 1;
    return query(ql, qr, qv, l, m, 2 * i + 1) + query(ql, qr, qv, m + 1, r, 2 * i + 2);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, C; cin >> N >> M >> C;
    for (int i = 1; i <= N; ++i) cin >> colour[i];
    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    DFS(1, 0);
    for (int i = 1; i <= N; ++i)
        recolour[in[i]] = colour[i];
    build_segT(1, N, 0);
    
    int ans = 0;
    while (M--) {
        int rt, c; cin >> rt >> c;
        ans = (ans + query(in[rt], out[rt], c, 1, N, 0)) % mod;
    }
    cout << ans;
    return 0;
}