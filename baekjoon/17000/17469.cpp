#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int max_N = 100001;
const int max_Q = 1100000;

int par[max_N];
unordered_set<int> c[max_N];
p query[max_Q];
int ans[max_Q];
int parent[max_N];

int _find(int u) {
    if (parent[u] < 0) return u;
    return parent[u] = _find(parent[u]);
}
void _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (u ^ v) {
        if (c[u].size() < c[v].size())
            swap(u, v);
        for (int colour : c[v])
            c[u].emplace(colour);
        parent[v] = u;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    int j = Q, k = Q;
    Q += N - 1;
    for (int i = 2; i <= N; ++i)
        cin >> par[i];
    for (int i = 1; i <= N; ++i) {
        int colour; cin >> colour;
        c[i].emplace(colour);
    }
    for (int i = Q; i--;)
        cin >> query[i].first >> query[i].second;

    memset(parent + 1, -1, sizeof(int) * N);
    for (int i = 0; i < Q; ++i) {
        auto& [q, n] = query[i];
        if (q == 1) _union(n, par[n]);
        else ans[--j] = c[_find(n)].size();
    }

    for (int i = 0; i < k; ++i)
        cout << ans[i] << '\n';
    return 0;
}