#include <bits/stdc++.h>
#define T(x) ((x-1)<<1)
#define F(x) (~x<<1|1)
#define N(x) (x^1)
using namespace std;

const int max_N = 20000;

int t, topo;
vector<int> adj[max_N];
int disc[max_N], low[max_N], scc[max_N];
bool on_stack[max_N];
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
    while (M--) {
        int x, y; cin >> x >> y;
        x = x > 0 ? T(x) : F(x);
        y = y > 0 ? T(y) : F(y);
        adj[N(x)].emplace_back(y);
        adj[N(y)].emplace_back(x);
    }

    for (int i = 0; i < N << 1; ++i)
        if (!disc[i] && dfs(i)) {
            cout << 0;
            return 0;
        }

    cout << 1 << '\n';
    for (int i = 0; i < N << 1; i += 2)
        cout << (scc[i] < scc[N(i)]) << ' ';
    return 0;
}