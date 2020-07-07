#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 5001;

int t, scc_cnt;
vector<int> adj[max_N];
vector<int> component[max_N];
int disc[max_N], low[max_N], scc[max_N];
bool out[max_N];
stack<int> stk;

void dfs(int u) {
    disc[u] = low[u] = ++t;
    stk.emplace(u);

    for (int& v : adj[u]) {
        if (!disc[v]) dfs(v);
        if (scc[v] == -1) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u]) {
        component[scc_cnt].clear();
        while (1) {
            int x = stk.top(); stk.pop();
            component[scc_cnt].emplace_back(x);
            scc[x] = scc_cnt;
            if (x == u) break;
        }
        ++scc_cnt;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
start:;
    int N, M; cin >> N;
    if (N == 0) return 0;

    t = 0, scc_cnt = 0;
    LOOP(i, N) adj[i].clear();
    memset(scc + 1, -1, sizeof(int) * N);
    memset(disc + 1, 0, sizeof(int) * N);
    memset(low + 1, 0, sizeof(int) * N);
    memset(out, 0, N);

    cin >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }

    LOOP(i, N) if (!disc[i])
        dfs(i);

    LOOP(u, N) for (int& v : adj[u])
        if (scc[u] ^ scc[v])
            out[scc[u]] = true;;

    vector<int> ans;
    for (int i = 0; i < scc_cnt; ++i)
        if (!out[i])
            for (int& u : component[i])
                ans.emplace_back(u);

    sort(ans.begin(), ans.end());
    for (int& u : ans) cout << u << ' ';
    cout << '\n';
    goto start;
}