#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 10;
//const int max_N = 100000;

int t, scc_cnt;
vector<int> adj[max_N];
vector<int> component[max_N];
int disc[max_N], low[max_N];
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
        component[scc_cnt].clear();
        while (1) {
            int x = stk.top(); stk.pop();
            component[scc_cnt].emplace_back(x);
            finished[x] = true;
            if (x == u) break;
        }
        ++scc_cnt;
    }
}
int dfs2(int u) {
    int ret = disc[u] = 1;
    for (int& v : adj[u])
        if (!disc[v])
            ret += dfs2(v);
    return ret;
}
void solve() {
    int N, M; cin >> N >> M;
    t = 0, scc_cnt = 0;
    loop(i, N) adj[i].clear();
    memset(disc, 0, sizeof(int) * N);
    memset(low, 0, sizeof(int) * N);
    memset(finished, 0, N);

    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }

    loop(i, N) if (!disc[i])
        dfs(i);

    vector<int>& rt = component[scc_cnt - 1];
    memset(disc, 0, sizeof(int) * N);

    if (dfs2(rt[0]) ^ N) cout << "Confused\n";
    else {
        sort(rt.begin(), rt.end());
        for (int& u : rt) cout << u << '\n';
    }
    cout << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}