#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int M = 100001;

vector<p> adj[M];
int sz[M], parent[M], dist[M];

vector<int> chain[M];
int depth[M];
int chain_number[M], chain_index[M];

vector<p> segT[M];

int DFS(int u, int p) {
    parent[u] = p;
    sz[u] = 1;
    for (auto [w, v] : adj[u]) if (v != p) {
        dist[v] = w;
        sz[u] += DFS(v, u);
    }
    return sz[u];
}
void HLD(int u, int p, int ch, int d) {
    depth[u] = d;
    chain_number[u] = ch;
    chain_index[u] = chain[ch].size();
    chain[ch].emplace_back(u);

    int H = -1;
    for (auto [w, v] : adj[u]) if (v != p)
        if (H == -1 || sz[v] > sz[H])
            H = v;

    if (H != -1)
        HLD(H, u, ch, d);
    for (auto [w, v] : adj[u]) if (v != p && v != H)
        HLD(v, u, v, d + 1);
}
p min_max(const p& a, const p& b) {
    p ret;
    ret.first = min(a.first, b.first);
    ret.second = max(a.second, b.second);
    return ret;
}
void build_segT(int ch, int l, int r, int idx) {
    if (l == r) {
        segT[ch][idx] = { dist[chain[ch][l]],dist[chain[ch][l]] };
        return;
    }

    int m = (l + r) / 2;
    int l_child = 2 * idx + 1, r_child = 2 * idx + 2;

    build_segT(ch, l, m, l_child);
    build_segT(ch, m + 1, r, r_child);
    segT[ch][idx] = min_max(segT[ch][l_child], segT[ch][r_child]);
}
p query(int ch, int ql, int qr, int l, int r, int idx) {
    if (ql <= l && r <= qr) return segT[ch][idx];
    if (qr < l || r < ql) return { INT_MAX,INT_MIN };

    int m = (l + r) / 2;
    return min_max(query(ch, ql, qr, l, m, 2 * idx + 1), query(ch, ql, qr, m + 1, r, 2 * idx + 2));
}
p solve(int u, int v) {
    p ret = { INT_MAX, INT_MIN };
    while (chain_number[u] != chain_number[v]) {
        if (depth[u] > depth[v]) {
            ret = min_max(ret, query(chain_number[u], 0, chain_index[u], 0, chain[chain_number[u]].size() - 1, 0));
            u = parent[chain_number[u]];
        }
        else {
            ret = min_max(ret, query(chain_number[v], 0, chain_index[v], 0, chain[chain_number[v]].size() - 1, 0));
            v = parent[chain_number[v]];
        }
    }
    if (chain_index[u] > chain_index[v]) swap(u, v);
    ret = min_max(ret, query(chain_number[u], chain_index[u] + 1, chain_index[v], 0, chain[chain_number[u]].size() - 1, 0));
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    DFS(1, 0);
    HLD(1, 0, 1, 0);

    for (int i = 1; i <= N; ++i) {
        int s = chain[i].size();
        if (s == 0) continue;

        segT[i].resize(2 * pow(2, ceil(log2(s))) - 1);
        build_segT(i, 0, s - 1, 0);
    }

    int Q; cin >> Q;
    while (Q--) {
        int u, v; cin >> u >> v;
        p ans = solve(u, v);
        cout << ans.first << ' ' << ans.second << '\n';
    }
    return 0;
}