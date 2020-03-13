// ** 감사합니다. polohee81 ** //
#include <bits/stdc++.h>
using namespace std;

int in[14];
bool node[14];
bool visited[14];
vector<int> adj[14];

bool DFS(int u) {
    if (visited[u]) return false;
    visited[u] = true;
    bool ret = true;
    for (int v : adj[u])
        ret &= DFS(v);
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int TC = 0;
    while (1) {
        int u, v; cin >> u >> v;
        if (u == -1) break;
        else if (u == 0) {
            cout << "Case " << ++TC << " is a tree.\n";
            continue;
        }
        memset(in, 0, sizeof(in));
        memset(node, 0, sizeof(node));
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= 13; ++i)
            adj[i].clear();

        bool is_tree = true;
        do {
            node[u] = node[v] = true;
            if (++in[v] > 1) is_tree = false;
            adj[u].emplace_back(v);
            cin >> u >> v;
        } while (u);
        
        int rt = -1;
        for (int i = 1; i <= 13; ++i) if (node[i] && !in[i]) {
            if (rt == -1) rt = i;
            else is_tree = false;
        }
        if (rt == -1) is_tree = false;
        if(!is_tree){
            cout << "Case " << ++TC << " is not a tree.\n";
            continue;
        }

        is_tree = DFS(rt);
        for (int i = 1; i <= 13; ++i)
            if (node[i] && !visited[i])
                is_tree = false;
        cout << "Case " << ++TC << " is";
        if (!is_tree) cout << " not";
        cout << " a tree.\n";
    }
    return 0;
}