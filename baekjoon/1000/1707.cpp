#include<bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_V = 20000;

vector<int> adj[max_V + 1];
bool visited[max_V + 1];
bool colour[max_V + 1];

bool is_bipartite(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            colour[v] = !colour[u];
            if (!is_bipartite(v))
                return false;
        }
        else if (colour[u] == colour[v])
            return false;
    }
    return true;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int V, E; cin >> V >> E;
        LOOP(i, V) adj[i].clear();
        while (E--) {
            int u, v; cin >> u >> v;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }

        // visited : 방문체크
        // colour : 해당 vertex의 색깔
        // DFS 중 같은 색깔끼리 인접하게 되면, 이분그래프가 아니다.
        memset(visited, 0, V + 1);
        memset(colour, 0, V + 1);

        bool flag = true;
        LOOP(i, V) if (!visited[i] && !is_bipartite(i)) {
            flag = false;
            break;
        }
        cout << (flag ? "YES" : "NO") << '\n';
    }
    return 0;
}