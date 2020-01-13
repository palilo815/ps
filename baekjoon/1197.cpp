#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
#define ll long long

int V, E;
vector<P> adj[10001];
ll Prim() {
    vector<bool> added(V + 1);
    vector<int> min_weight(V + 1, INT32_MAX);
    ll ret = 0;
    min_weight[1] = 0;

    for (int iter = 1;iter <= V;++iter) {
        int u = -1;
        for (int v = 1;v <= V;++v)
            if (!added[v] && (u == -1 || min_weight[u] > min_weight[v]))
                u = v;

        ret += (ll)min_weight[u];
        added[u] = true;

        int len = adj[u].size();
        loop(i, len) {
            int v = adj[u][i].first, weight = adj[u][i].second;
            if (!added[v] && min_weight[v] > weight)
                min_weight[v] = weight;
        }
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> V >> E;
    loop(i, E) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    cout << Prim();
    return 0;
}