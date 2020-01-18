#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

vector<P> adj[1001];
int max_scr[1001], cache[1001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, scr; cin >> u >> v >> scr;
        adj[u].push_back({ v,scr });
    }

    queue<P> q;
    loop(i, adj[1].size()) {
        int v = adj[1][i].first, scr = adj[1][i].second;
        max_scr[v] = scr;
        cache[v] = 1;
        q.push({ v,scr });
    }

    while (!q.empty()) {
        int u = q.front().first, scr = q.front().second; q.pop();
        if (u == 1 || max_scr[u] > scr) continue;
        loop(i, adj[u].size()) {
            int v = adj[u][i].first, v_scr = scr + adj[u][i].second;
            if (max_scr[v] < v_scr) {
                max_scr[v] = v_scr;
                cache[v] = u;
                q.push({ v,v_scr });
            }
        }
    }
    cout << max_scr[1] << '\n';
    stack<int> path;
    path.push(1);
    int pos = cache[1];
    while (pos != 1) {
        path.push(pos);
        pos = cache[pos];
    }
    cout << 1;
    while (!path.empty()) {
        cout << ' ' << path.top();
        path.pop();
    }
    return 0;
}