#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

stack<int> stk;
vector<int> adj[max_N + 1];
bool visited[max_N + 1];

void DFS(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v])
        DFS(v);
    stk.push(u);
}
void knock(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v])
        knock(v);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    
    // ** topological sort **

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        for (int i = 1; i <= N; ++i) adj[i].clear();
        while (M--) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
        }

        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= N; ++i) if (!visited[i])
            DFS(i);

        memset(visited, 0, sizeof(visited));
        int ans = 0;
        while (!stk.empty()) {
            int u = stk.top(); stk.pop();
            if (!visited[u]) {
                knock(u);
                ++ans;
            }
        }
        cout << ans << '\n';
    }
    return 0;
    
}