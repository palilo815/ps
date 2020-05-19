#include <bits/stdc++.h>
using namespace std;
typedef vector<int> VI;

const int max_N = 100001;
const int seg_N = 131072 * 2 - 1;

int arr_D[max_N];
int elr_D[max_N];
vector<int> adj[max_N];
int segT[seg_N];
int lazy[seg_N];

int _time;
int in[max_N];
int out[max_N];

void DFS(int u, int p) {
    in[u] = ++_time;
    for (int v : adj[u]) if (v != p)
        DFS(v, u);
    out[u] = _time;
}
int build_segT(int l, int r, int i) {
    if (l == r) return segT[i] = elr_D[l];

    int m = (l + r) >> 1;
    return segT[i] = build_segT(l, m, 2 * i + 1) ^ build_segT(m + 1, r, 2 * i + 2);
}
void update(int ql, int qr, int qv, int l, int r, int i) {
    if (lazy[i]) {
        if ((r - l + 1) & 1) segT[i] ^= lazy[i];
        if (l != r) {
            lazy[2 * i + 1] ^= lazy[i];
            lazy[2 * i + 2] ^= lazy[i];
        }
        lazy[i] = 0;
    }

    if (ql <= l && r <= qr) {
        if ((r - l + 1) & 1) segT[i] ^= qv;
        if (l != r) {
            lazy[2 * i + 1] ^= qv;
            lazy[2 * i + 2] ^= qv;
        }
        return;
    }
    if (qr < l || r < ql) return;

    int m = (l + r) >> 1;
    update(ql, qr, qv, l, m, 2 * i + 1);
    update(ql, qr, qv, m + 1, r, 2 * i + 2);
    segT[i] = segT[2 * i + 1] ^ segT[2 * i + 2];
}
int query(int ql, int qr, int l, int r, int i) {
    if (lazy[i]) {
        if ((r - l + 1) & 1) segT[i] ^= lazy[i];
        if (l != r) {
            lazy[2 * i + 1] ^= lazy[i];
            lazy[2 * i + 2] ^= lazy[i];
        }
        lazy[i] = 0;
    }

    if (ql <= l && r <= qr) return segT[i];
    if (qr < l || r < ql) return 0;

    int m = (l + r) >> 1;
    return query(ql, qr, l, m, 2 * i + 1) ^ query(ql, qr, m + 1, r, 2 * i + 2);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for (int i = 1; i <= N; ++i)
        cin >> arr_D[i];

    DFS(1, 0);

    for (int i = 1; i <= N; ++i)
        elr_D[in[i]] = arr_D[i];

    build_segT(1, N, 0);

    while (M--) {
        int q; cin >> q;
        if (q == 1) {
            int i; cin >> i;
            cout << query(in[i], out[i], 1, N, 0) << '\n';
        }
        else {
            int i, v; cin >> i >> v;
            update(in[i], out[i], v, 1, N, 0);
        }
    }
    return 0;
}