#include <bits/stdc++.h>
#define N(x) (x^1)
using namespace std;

const int max_M = 1000000;

int t, topo;
vector<int> adj[max_M];
int disc[max_M], low[max_M], scc[max_M];
bool on_stack[max_M];
stack<int> stk;

bool dfs(int u) {
    disc[u] = low[u] = ++t;
    stk.emplace(u);
    on_stack[u] = true;

    for (int& v : adj[u]) {
        if (!disc[v] && dfs(v)) return true;
        if (on_stack[v]) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u]) {
        ++topo;
        while (1) {
            int x = stk.top(); stk.pop();
            on_stack[x] = false;
            scc[x] = topo;
            if (scc[x] == scc[N(x)]) return true;
            if (x == u) break;
        }
    }
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    while (N--) {
        int x, s1, y, s2; cin >> x >> s1 >> y >> s2;
        x = (x - 1) << 1 ^ s1;
        y = (y - 1) << 1 ^ s2;
        adj[N(x)].emplace_back(y);
        adj[N(y)].emplace_back(x);
    }

    for (int i = 0; i < M << 1; ++i)
        if (!disc[i] && dfs(i)) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    for (int i = 0; i < M << 1; i += 2)
        cout << (scc[i] > scc[N(i)]) << '\n';
    return 0;
}