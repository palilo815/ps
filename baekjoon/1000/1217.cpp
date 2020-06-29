#include <bits/stdc++.h>
#define T(x) ((x-1)<<1)
#define F(x) (~x<<1|1)
#define N(x) (x^1)
using namespace std;

const int max_M = 40000;

int t;
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

    if (disc[u] == low[u])
        while (1) {
            int x = stk.top(); stk.pop();
            on_stack[x] = false;
            scc[x] = low[u];
            if (scc[x] == scc[N(x)]) return true;
            if (x == u) break;
        }
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
start:;
    int N, M; cin >> N >> M;
    if (!N) return 0;

    M <<= 1;
    t = 0;
    for (int i = 0; i < M; ++i)
        adj[i].clear();
    memset(disc, 0, sizeof(int) * M);
    memset(low, 0, sizeof(int) * M);
    memset(scc, 0, sizeof(int) * M);

    while (N--) {
        int x, y; cin >> x >> y;
        x = x > 0 ? T(x) : F(x);
        y = y > 0 ? T(y) : F(y);
        adj[x].emplace_back(N(y));
        adj[y].emplace_back(N(x));
    }

    for (int i = 0; i < M; ++i)
        if (!disc[i] && dfs(i)) {
            cout << "0\n";
            goto start;
        }
    cout << "1\n";
    goto start;
}