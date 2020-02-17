#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

vector<int> adj[max_N + 1];
vector<int> Euler_tour;
int occurrence[max_N + 1];

int cnt;
int Euler_idx[max_N + 1];
int original_idx[max_N];

int segT[262144 * 2 - 1];

void touring(int u, int p)
{
    original_idx[cnt] = u;
    Euler_idx[u] = cnt;
    occurrence[u] = Euler_tour.size();
    ++cnt;
    Euler_tour.push_back(Euler_idx[u]);
    for (int v : adj[u]) if (v != p) {
        touring(v, u);
        Euler_tour.push_back(Euler_idx[u]);
    }
}
int build_segT(int l, int r, int idx)
{
    if (l == r) return segT[idx] = Euler_tour[l];
    int m = l + (r - l) / 2;
    return segT[idx] = min(build_segT(l, m, 2 * idx + 1), build_segT(m + 1, r, 2 * idx + 2));
}
int query(int ql, int qr, int l, int r, int idx)
{
    if (ql <= l && r <= qr) return segT[idx];
    if (qr < l || r < ql) return INT_MAX;
    int m = l + (r - l) / 2;
    return min(query(ql, qr, l, m, 2 * idx + 1), query(ql, qr, m + 1, r, 2 * idx + 2));
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Euler_tour.reserve(2 * N - 1);
    touring(1, -1);
    build_segT(0, 2 * N - 2, 0);

    int Q; cin >> Q;
    while (Q--) {
        int a, b; cin >> a >> b;
        int ql = occurrence[a], qr = occurrence[b];
        if (ql > qr) swap(ql, qr);
        int q = query(ql, qr, 0, 2 * N - 2, 0);
        cout << original_idx[q] << '\n';
    }
    return 0;
}