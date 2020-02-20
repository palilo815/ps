#include <bits/stdc++.h>
using namespace std;

const int max_N = 300;
const int max_M = 300;

bool visited[max_M + 1];
vector<int> adj[max_N + 1];

int N_match[max_N + 1];
int M_match[max_M + 1];

bool DFS(int u)
{
    if (visited[u]) return false;
    visited[u] = true;
    for(int v : adj[u])
        if (!M_match[v] || DFS(M_match[v])) {
            N_match[u] = v;
            M_match[v] = u;
            return true;
        }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K1, K2; cin >> N >> M >> K1 >> K2;
    while (K1--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }

    int ally = 0;
    for (int i = 1; i <= N; ++i) {
        memset(visited, 0, sizeof(visited));
        if (DFS(i)) ++ally;
    }

    memset(N_match, 0, sizeof(N_match));
    memset(M_match, 0, sizeof(M_match));
    for (int i = 1; i <= N; ++i) adj[i].clear();

    while (K2--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }

    int enemy = 0;
    for (int i = 1; i <= N; ++i) {
        memset(visited, 0, sizeof(visited));
        if (DFS(i)) ++enemy;
    }

    if (ally < enemy) cout << "네 다음 힐딱이";
    else cout << "그만 알아보자";
    return 0;
}