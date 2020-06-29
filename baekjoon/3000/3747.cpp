#include <bits/stdc++.h>
#define T(x) ((x-1)<<1)
#define F(x) (~x<<1|1)
#define N(x) (x^1)
using namespace std;

const int max_N = 2000;

int t;
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

    int N, M;
    while (cin >> N >> M) {
        t = 0;
        N <<= 1;
        for (int i = 0; i < N; ++i)
            adj[i].clear();
        memset(disc, 0, sizeof(int) * N);
        memset(low, 0, sizeof(int) * N);
        memset(scc, 0, sizeof(int) * N);

        while (M--) {
            int x, y; cin >> x >> y;
            x = x > 0 ? T(x) : F(x);
            y = y > 0 ? T(y) : F(y);
            adj[N(x)].emplace_back(y);
            adj[N(y)].emplace_back(x);
        }

        char ans = '1';
        for (int i = 0; i < N; ++i)
            if (!disc[i] && dfs(i)) {
                ans = '0';
                break;
            }
        cout << ans << '\n';
    }
    return 0;
}