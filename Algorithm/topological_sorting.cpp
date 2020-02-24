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
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 1; i <= N; ++i) if (!visited[i])
        DFS(i);

    while (!stk.empty()) {
        cout << stk.top() << ' ';
        stk.pop();
    }
    return 0;

}