#include <bits/stdc++.h>
using namespace std;

const int max_N = 100001;

vector<int> adj[max_N];

int _time;
int in[max_N];
int out[max_N];

int segT[131072 * 2 - 1];
char lazy[131072 * 2 - 1];

void DFS(int u) {
    in[u] = ++_time;
    for (int v : adj[u]) DFS(v);
    out[u] = _time;
}
int init(int l, int r, int i) {
    if (l == r) return segT[i] = 1;
    int m = (l + r) >> 1;
    return segT[i] = init(l, m, 2 * i + 1) + init(m + 1, r, 2 * i + 2);
}
void update(int ql, int qr, char qv, int l, int r, int i) {
    if (lazy[i]) {
        segT[i] = ((lazy[i] == '1') ? (r - l + 1) : 0);
        if (l != r) {
            lazy[2 * i + 1] = lazy[i];
            lazy[2 * i + 2] = lazy[i];
        }
        lazy[i] = 0;
    }

    if (ql <= l && r <= qr) {
        segT[i] = ((qv == '1') ? (r - l + 1) : 0);
        if (l != r) {
            lazy[2 * i + 1] = qv;
            lazy[2 * i + 2] = qv;
        }
        return;
    }
    if (qr < l || r < ql) return;

    int m = (l + r) >> 1;
    update(ql, qr, qv, l, m, 2 * i + 1);
    update(ql, qr, qv, m + 1, r, 2 * i + 2);
    segT[i] = segT[2 * i + 1] + segT[2 * i + 2];
}
int query(int ql, int qr, int l, int r, int i) {
    if (lazy[i]) {
        segT[i] = ((lazy[i] == '1') ? (r - l + 1) : 0);
        if (l != r) {
            lazy[2 * i + 1] = lazy[i];
            lazy[2 * i + 2] = lazy[i];
        }
        lazy[i] = 0;
    }

    if (ql <= l && r <= qr) return segT[i];
    if (qr < l || r < ql) return 0;

    int m = (l + r) >> 1;
    return query(ql, qr, l, m, 2 * i + 1) + query(ql, qr, m + 1, r, 2 * i + 2);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    int u; cin >> u;
    for (int v = 2; v <= N; ++v) {
        cin >> u;
        adj[u].emplace_back(v);
    }

    DFS(1);
    init(1, N, 0);

    int Q; cin >> Q;
    while (Q--) {
        int q, i; cin >> q >> i;
        int ql = in[i] + 1, qr = out[i];
        if (q == 1) update(ql, qr, '1', 1, N, 0);
        else if (q == 2) update(ql, qr, '0', 1, N, 0);
        else cout << query(ql, qr, 1, N, 0) << '\n';
    }
    return 0;
}