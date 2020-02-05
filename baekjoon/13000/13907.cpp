#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;
typedef pair<int, int> P;
const int max_N = 1000;

vector<P> adj[max_N + 1];
int cost[max_N + 1][max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K, src, dst;
    cin >> N >> M >> K >> src >> dst;

    while (M--) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    // cost [idx][edge] : idx번 도시를 edge개의 도로를 사용해서 가는 최소비용
    for (int i = 1; i <= N; ++i) {
        if (i == src) continue;
        for (int j = 0; j < N; ++j)
            cost[i][j] = INT_MAX;
    }

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.push({ 0,0,src });
    int max_edge = INT_MAX;
    while (!pq.empty()) {
        int pay = get<0>(pq.top());
        int edges = get<1>(pq.top());
        int u = get<2>(pq.top());
        pq.pop();

        // dst를 처음 발견하면 max_edge를 갱신해준다.
        // max_edge보다 많은 edge는 고려할 필요가 없다.
        // (세금이 올라갈수록 최소비용보다 비싸지기 때문)
        if (u == dst) {
            if (edges > max_edge) continue;
            if (max_edge == INT_MAX) max_edge = edges;
            cost[u][edges] = min(cost[u][edges], pay);
        }

        // 도시가 N개라면, <=N-1개의 도로를 사용하는 경우만 고려하면 된다.
        if (cost[u][edges] < pay || edges == N - 1) continue;

        for (P p : adj[u]) {
            int next_pay = pay + p.first, v = p.second;
            if (cost[v][edges + 1] > next_pay) {
                cost[v][edges + 1] = next_pay;
                pq.push({ next_pay,edges + 1,v });
            }
        }
    }

    // [min_edge, max_edge] 구간이 후보다.
    int min_edge = 0;
    while (cost[dst][min_edge] == INT_MAX) ++min_edge;
    cout << cost[dst][max_edge] << '\n';
    
    // 세금이 add원 올라갈 때마다
    // [min_edge, max_edge] 구간의 cost를 add * edge만큼 늘려준다.
    // 늘려 준 후 최솟값의 index를 idx라고 하면,
    // 세금이 늘면 늘 수록, idx보다 많은 edge를 가진 경로는 idx 경로보다 무조건 비싸지게 되므로
    // max_edge 범위를 idx로 바꿀 수 있다.
    int add, min_cost, idx;
    while (K--) {
        cin >> add;
        min_cost = INT_MAX;
        for (int i = min_edge; i <= max_edge; ++i) {
            cost[dst][i] += add * i;
            if (cost[dst][i] < min_cost) {
                min_cost = cost[dst][i];
                idx = i;
            }
        }
        cout << min_cost << '\n';
        max_edge = idx;
    }
    return 0;
}