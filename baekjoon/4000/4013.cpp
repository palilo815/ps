#include <bits/stdc++.h>
using namespace std;

const int max_N = 500001;

int t, scc_cnt;
vector<int> adj[max_N];
vector<vector<int>> components;
int disc[max_N], low[max_N], scc[max_N];
stack<int> stk;

int ATM[max_N];
bool dst[max_N];

void dfs(int u) {
    disc[u] = low[u] = ++t;
    stk.emplace(u);

    for (int& v : adj[u]) {
        if (!disc[v]) dfs(v);
        if (scc[v] == -1) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u]) {
        vector<int> tmp;
        while (1) {
            int x = stk.top(); stk.pop();
            tmp.emplace_back(x);
            scc[x] = scc_cnt;
            if (x == u) break;
        }
        components.emplace_back(tmp);
        ++scc_cnt;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }
    for (int i = 1; i <= N; ++i)
        cin >> ATM[i];

    int src, K; cin >> src >> K;
    while (K--) {
        int x; cin >> x;
        dst[x] = true;
    }

    memset(scc + 1, -1, sizeof(int) * N);
    for (int i = 1; i <= N; ++i)
        if (!disc[i])
            dfs(i);

    int* DP = disc;
    memset(DP, 0, sizeof(int) * scc_cnt);
    DP[scc[src]] = 1;

    for (int i = scc[src]; i >= 0; --i) {
        if (DP[i])
            for (int& u : components[i])
                DP[i] += ATM[u];
        for (int& u : components[i])
            for (int& v : adj[u])
                if (scc[u] ^ scc[v])
                    DP[scc[v]] = max(DP[scc[v]], DP[scc[u]]);
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i)
        if (dst[i])
            ans = max(ans, DP[scc[i]]);
    cout << (ans ? ans - 1 : 0);
    return 0;
}