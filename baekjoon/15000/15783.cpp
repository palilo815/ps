#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;

vector<int> adj[max_N];
bool in[max_N];

stack<int> stk, tp;
int disc[max_N], low[max_N];
bool on_stack[max_N];
int t;

void dfs1(int u) {
    disc[u] = -1;
    for (int& v : adj[u])
        if (disc[v] != -1)
            dfs1(v);
}
void dfs2(int u) {
    disc[u] = low[u] = ++t;
    stk.emplace(u);
    on_stack[u] = true;

    for (int& v : adj[u]) {
        if (!disc[v]) dfs2(v);
        if (on_stack[v]) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u]) {
        tp.emplace(u);
        while (1) {
            int x = stk.top(); stk.pop();
            on_stack[x] = false;
            if (x == u) break;
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        in[v] = true;
    }

    int ans = 0;
    loop(i, N) if (!in[i]) {
        ++ans;
        dfs1(i);
    }
    loop(i, N) if (!disc[i])
        dfs2(i);
    while (!tp.empty()) {
        int i = tp.top(); tp.pop();
        if (disc[i] != -1) {
            ++ans;
            dfs1(i);
        }
    }
    cout << ans;
    return 0;
}