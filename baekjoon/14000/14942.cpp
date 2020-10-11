#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 1;
const int mxD = 17;

vector<pair<int, int>> adj[mxN];
vector<int> dist, idx;
int a[mxN], ans[mxN];

void dfs(int u, int p) {
    ans[u] = idx[lower_bound(dist.begin(), dist.end(), dist.back() - a[u]) - dist.begin()];
    for (auto& [w, v] : adj[u]) {
        if (v == p) continue;
        dist.emplace_back(dist.back() + w);
        idx.emplace_back(v);
        dfs(v, u);
        dist.pop_back();
        idx.pop_back();
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; ++i)
        scanf("%d", &a[i]);

    for (int i = 1, u, v, w; i < N; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    dist.emplace_back(0);
    idx.emplace_back(1);
    dfs(1, 0);

    for (int i = 1; i <= N; ++i)
        printf("%d\n", ans[i]);
    return 0;
}