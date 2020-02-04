#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<ll, int, int> tup;
typedef pair<int, int> P;
const int max_V = 2500;
const int max_P = 2500;

// 도시의 기름 가격 저장
int price[max_V + 1];

// i도시에서 j원의 최저가 기름을 산 채로 도착하기 위한 최소비용
ll min_cost[max_V + 1][max_P + 1];

// 그래프
vector<P> adj[max_V + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    // ** initialize **
    // Dijkstra를 위해 전부 INF로 초기화
    int V, E; cin >> V >> E;
    for (int i = 1; i <= V; ++i)
        for (int j = 1; j <= max_P; ++j)
            min_cost[i][j] = INT64_MAX;

    // ** input **
    for (int i = 1; i <= V; ++i)
        cin >> price[i];
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ v,w });
        adj[v].push_back({ u,w });
    }

    // tup 구성
    // 1. 사용한 돈
    // 2. vertex_idx
    // 3. 방문한 도시 중 기름 최저가
    priority_queue<tup, vector<tup>, greater<tup>> pq;
    min_cost[1][price[1]] = 0;
    pq.push({ 0,1,price[1] });

    // 항상 dst에 도착할 수 있다고 문제에서 보장함
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