#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<ll, int, int> tup;
typedef pair<int, int> P;
const int max_V = 2500;
const int max_P = 2500;

int price[max_V + 1];
ll min_cost[max_V + 1][max_P + 1];
vector<P> adj[max_V + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    for (int i = 1; i <= V; ++i)
        for (int j = 1; j <= max_P; ++j)
            min_cost[i][j] = INT64_MAX;
    for (int i = 1; i <= V; ++i)
        cin >> price[i];
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ v,w });
        adj[v].push_back({ u,w });
    }

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    min_cost[1][price[1]] = 0;
    pq.push({ 0,1,price[1] });
    while (1) {
        ll cost = get<0>(pq.top());
        int u = get<1>(pq.top());
        int min_price = get<2>(pq.top());
        pq.pop();

        if (u == V) { cout << cost; break; }
        if (min_cost[u][min_price] < cost) continue;

        min_price = min(min_price, price[u]);

        for (P p : adj[u]) {
            int v = p.first;
            ll D = cost + p.second * min_price;
            if (min_cost[v][min_price] > D) {
                min_cost[v][min_price] = D;
                pq.push({ D,v,min_price });
            }
        }
    }
    return 0;
}