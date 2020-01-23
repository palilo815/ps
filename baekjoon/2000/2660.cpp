#include<bits/stdc++.h>
using namespace std;
#define LOOP(i,n) for(int i=1;i<=n;++i)

int adj[51][51];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V; cin >> V;
    LOOP(i, V) LOOP(j, V) adj[i][j] = INT32_MAX / 2;
    LOOP(i, V) adj[i][i] = 0;

    while (1) {
        int u, v; cin >> u >> v;
        if (u == -1) break;
        adj[u][v] = 1, adj[v][u] = 1;
    }

    // Floyd-Warshall
    LOOP(k, V) LOOP(i, V) LOOP(j, V)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

    int HEAD = INT32_MAX;
    vector<int> ans;
    LOOP(i, V) {
        int score = 0;
        LOOP(j, V) score = max(score, adj[i][j]);
        if (score == HEAD)
            ans.push_back(i);
        else if (score < HEAD) {
            ans.clear();
            HEAD = score;
            ans.push_back(i);
        }
    }
    cout << HEAD << ' ' << ans.size() << '\n';
    for (int n : ans)
        cout << n << ' ';
    return 0;
}