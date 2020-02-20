#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000;
const int max_M = 1000;

vector<int> adj[max_N + 1];
bool visited[max_M + 1];
int N_match[max_N + 1];
int M_match[max_M + 1];

bool DFS(int u)
{
    if (visited[u]) return false;
    visited[u] = true;
    for(int v:adj[u])
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

    int N, M; cin >> N >> M;
    for (int u = 1; u <= N; ++u) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int v; cin >> v;
            adj[u].push_back(v);
        }
    }

    int ans = 0;
    for (int u = 1; u <= N; ++u) {
        memset(visited, 0, sizeof(visited));
        if (DFS(u)) ++ans;
    }
    cout << ans;
    return 0;
}