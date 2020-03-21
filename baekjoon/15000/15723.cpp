#include <bits/stdc++.h>
using namespace std;

int adj[26];
bool visited[26];

bool DFS(int u, int dst) {
    if (u == -1 || visited[u]) return false;
    if (u == dst) return true;
    visited[u] = true;
    return DFS(adj[u], dst);
}
int main() {
    char u, v;
    string s;
    memset(adj, -1, sizeof(adj));

    int N; cin >> N;
    while (N--) {
        cin >> u >> s >> v;
        adj[u - 'a'] = v - 'a';
    }

    int M; cin >> M;
    while (M--) {
        memset(visited, 0, sizeof(visited));
        cin >> u >> s >> v;
        cout << (DFS(u - 'a', v - 'a') ? 'T' : 'F') << '\n';
    }
    return 0;
}