#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_V = 1000;

vector<P> adj[max_V + 1];
bool selected[max_V + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, K; cin >> V >> E >> K;

    vector<int> initial(K);
    loop(i, K) {
        cin >> initial[i];
        selected[initial[i]] = true;
    }

    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    priority_queue<P, vector<P>, greater<P>> pq;
    for (int u : initial)
        for (P p : adj[u])
            if (!selected[p.second])
                pq.push(p);

    int ans = 0;
    while (!pq.empty()) {
        int u = pq.top().second, cost = pq.top().first; pq.pop();
        if (selected[u]) continue;
        selected[u] = true;
        ans += cost;
        for (P p : adj[u])
            if (!selected[p.second])
                pq.push(p);
    }
    cout << ans;
    return 0;
}