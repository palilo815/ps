#include <bits/stdc++.h>
using namespace std;

const int mxN = 3e4;
const int mxK = 3e3;

int par[mxN], c[mxN], dp[mxK];

int find(int u) {
    return par[u] < 0 ? u : par[u] = find(par[u]);
}
void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;

    c[u] += c[v];
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i)
        cin >> c[i];

    memset(par, -1, sizeof(int) * n);
    for (int u, v; m--;) {
        cin >> u >> v;
        merge(u - 1, v - 1);
    }

    memset(dp, -1, sizeof(int) * k);
    dp[0] = 0;

    for (int i = 0; i < n; ++i)
        if (par[i] < 0)
            for (int j = k + par[i] - 1; j >= 0; --j)
                if (~dp[j])
                    dp[j - par[i]] = max(dp[j - par[i]], dp[j] + c[i]);
    cout << *max_element(dp, dp + k);
}