#include <bits/stdc++.h>
#define T(x) ((x-1)<<1)
#define F(x) (T(x)|1)
#define N(x) (x^1)
using namespace std;

const int MAX = 4000;
const string ans[2] = {"Yes", "No"};

int t, id;
vector<int> adj[MAX];
int disc[MAX], low[MAX], scc[MAX];
bool on_stack[MAX];
stack<int> stk;

void dfs(int u) {
    disc[u] = low[u] = ++t;
    on_stack[u] = true;
    stk.emplace(u);

    for (int& v : adj[u]) {
        if (!disc[v]) dfs(v);
        if (on_stack[v]) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u]) {
        ++id;
        while (1) {
            int x = stk.top(); stk.pop();
            on_stack[x] = false;
            scc[x] = id;
            if (x == u) break;
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
start:;
    int N, M, K; cin >> N >> M >> K;
    int cnt = (N + M) << 1;
    for (int i = 0; i < cnt; ++i)
        adj[i].clear();
    memset(disc, 0, sizeof(int) * cnt);
    memset(low, 0, sizeof(int) * cnt);
    memset(scc, 0, sizeof(int) * cnt);


    while (K--) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        if (r1 == r2 && c1 == c2) continue;
        c1 += N, c2 += N;
        r1 < r2 ? (c1 = T(c1), c2 = T(c2)) : (c1 = F(c1), c2 = F(c2));
        c1 < c2 ? (r1 = T(r1), r2 = T(r2)) : (r1 = F(r1), r2 = F(r2));
        if (r1 == r2)
            adj[N(r1)].emplace_back(r1);
        else if (c1 == c2)
            adj[N(c1)].emplace_back(c1);
        else {
            adj[N(r1)].emplace_back(c1);
            adj[N(r1)].emplace_back(r2);
            adj[N(c1)].emplace_back(r1);
            adj[N(c1)].emplace_back(c2);
            adj[N(r2)].emplace_back(r1);
            adj[N(r2)].emplace_back(c2);
            adj[N(c2)].emplace_back(c1);
            adj[N(c2)].emplace_back(r2);
        }
    }

    for (int i = 0; i < cnt; ++i)
        if (!disc[i])
            dfs(i);

    int flag = 0;
    for (int i = 0; i < cnt; i += 2)
        if (scc[i] == scc[N(i)]) {
            flag = 1;
            break;
        }
    cout << ans[flag] << '\n';
    if (--T) goto start;
    return 0;
}