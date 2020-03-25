#include <bits/stdc++.h> 
using namespace std;
typedef pair<int, int> p;

const int max_V = 100000;

vector<p> adj[max_V + 1];
int dia[max_V + 1];
bool visited[max_V + 1];

int BFS(int src, int V) {
    memset(visited, 0, sizeof(visited));
    memset(dia, 0, sizeof(dia));

    queue<int> q;
    q.emplace(src);
    visited[src] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [w, v] : adj[u]) if (!visited[v]) {
            visited[v] = true;
            dia[v] += dia[u] + w;
            q.emplace(v);
        }
    }
    return int(max_element(dia + 1, dia + V + 1) - dia);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V; cin >> V;
    for (int i = 1; i <= V; ++i) {
        int u, v, w;
        cin >> u;
        while (1) {
            cin >> v;
            if (v == -1) break;
            cin >> w;
            adj[u].emplace_back(w, v);
        }
    }

    int src = BFS(1, V);
    int ans = BFS(src, V);
    cout << dia[ans];
    return 0;
}