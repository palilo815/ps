#include <bits/stdc++.h>
using namespace std;

const int max_N = 10001;

int t, scc_cnt = -1;
vector<int> adj[max_N];
vector<vector<int>> components;
int disc[max_N], low[max_N], scc[max_N], DP[max_N - 1];
bool finished[max_N];
stack<int> stk;

void dfs(int u) {
    disc[u] = low[u] = ++t;
    stk.emplace(u);

    for (int& v : adj[u]) {
        if (!disc[v]) dfs(v);
        if (!finished[v]) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u]) {
        ++scc_cnt;
        vector<int> tmp;
        while (1) {
            int x = stk.top(); stk.pop();
            tmp.emplace_back(x);
            scc[x] = scc_cnt, finished[x] = true;
            if (x == u) break;
        }
        components.emplace_back(tmp);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, src, dst;
    cin >> N >> M >> src >> dst;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }

    for (int i = 1; i <= N; ++i)
        if (!disc[i])
            dfs(i);

    DP[scc[src]] = 1;
    for (int i = scc[src]; i >= 0; --i) {
        if (DP[i]) DP[i] += components[i].size();
        for (int& u : components[i])
            for (int& v : adj[u])
                if (scc[u] ^ scc[v])
                    DP[scc[v]] = max(DP[scc[v]], DP[scc[u]]);
        if (i == scc[dst]) break;
    }
    cout << (DP[scc[dst]] ? DP[scc[dst]] - 1 : 0);
    return 0;
}