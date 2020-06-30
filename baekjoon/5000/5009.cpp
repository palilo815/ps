#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define T(x) (x<<1)
#define F(x) (T(x)|1)
#define N(x) (x^1)
using namespace std;

const int M = 200;

int N;
int prof[M];
int love[M][M - 1];

int t;
vector<int> adj[M << 1];
int disc[M << 1], low[M << 1], scc[M << 1];
bool on_stack[M << 1];
stack<int> stk;

void graph(int k) {
    t = 0;
    loop(i, N << 1) adj[i].clear();
    memset(disc, 0, sizeof(int) * (N << 1));
    memset(low, 0, sizeof(int) * (N << 1));
    memset(scc, 0, sizeof(int) * (N << 1));

    loop(x, N) {
        for (int i = k; i < N - 1; ++i) {
            int y = love[x][i];
            if (prof[x] == prof[y]) {
                adj[T(x)].emplace_back(F(y));
                adj[T(y)].emplace_back(F(x));
                adj[F(x)].emplace_back(T(y));
                adj[F(y)].emplace_back(T(x));
            }
            else if ((prof[x] + 1) % 3 == prof[y]) {
                adj[F(x)].emplace_back(F(y));
                adj[T(y)].emplace_back(T(x));
            }
            else {
                adj[T(x)].emplace_back(T(y));
                adj[F(y)].emplace_back(F(x));
            }
        }
    }
}
void dfs(int u) {
    disc[u] = low[u] = ++t;
    on_stack[u] = true;
    stk.emplace(u);

    for (int& v : adj[u]) {
        if (!disc[v]) dfs(v);
        if (on_stack[v]) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u])
        while (1) {
            int x = stk.top(); stk.pop();
            on_stack[x] = false;
            scc[x] = low[u];
            if (x == u) break;
        }
}
int solve() {
    loop(i, N << 1) if (!disc[i])
        dfs(i);

    for (int i = 0; i < N << 1; i += 2)
        if (scc[i] == scc[N(i)])
            return 1;
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) {
        cin >> prof[i];
        loop(j, N - 1) cin >> love[i][j];
        loop(j, N - 1) --love[i][j];
    }

    int l = 0, r = N - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        graph(m);
        solve() ? (l = m + 1) : (r = m);
    }
    cout << l << '\n';
    return 0;
}