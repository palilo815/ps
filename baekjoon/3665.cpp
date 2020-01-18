#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool adj[501][501];
int prev_rank[500], degree[501];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        memset(adj, 0, sizeof(adj));
        int n; cin >> n;
        loop(i, n) cin >> prev_rank[i];
        loop(i, n) for (int j = i + 1; j < n; ++j)
            adj[prev_rank[i]][prev_rank[j]] = true;

        int m; cin >> m;
        while (m--) {
            int u, v; cin >> u >> v;
            adj[u][v] = !adj[u][v];
            adj[v][u] = !adj[v][u];
        }

        for (int i = 1; i <= n; ++i) {
            int tmp = 0;
            for (int j = 1; j <= n; ++j)
                if (adj[j][i]) ++tmp;
            degree[i] = tmp;
        }

        queue<int> q;
        vector<int> ans;
        for (int i = 1; i <= n; ++i)
            if (!degree[i])
                q.push(i);
        while (!q.empty()) {
            int here = q.front(); q.pop();
            ans.push_back(here);
            for (int i = 1; i <= n; ++i) {
                if (adj[here][i]) {
                    if (--degree[i] == 0)
                        q.push(i);
                }
            }
        }

        if (ans.size() == n)
            for (int x : ans) cout << x << ' ';
        else cout << "IMPOSSIBLE";
        cout << '\n';
    }
    return 0;
}