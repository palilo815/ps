#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;
typedef pair<int, int> P;
const int max_N = 1000;

vector<P> adj[max_N + 1];
int cost[max_N + 1];
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

    for (int i = 1; i <= N; ++i)
        cost[i] = INT_MAX;
    cost[src] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.push({ 0,0,src });
    int max_edge = INT_MAX;

    // 못 풀었다.

    // 접근법 : src -> dst로 가는 최소비용이 cost, 이용한 도로가 edge개라면
    // src -> dst로 edge개 이하로 도로를 사용하는 모든 경우의 수를 구해놓는다.
    // 만약 i번째 세금 인상이 됐을 때
    // e개를 이용한 경로가 최소비용이라면
    // i 이후의 세금 인상에서 e개 보다 많은 도로를 사용한 경로는 절대 최솟값이 될 수 없다.

    // 문제점 : src -> dst로 가는 edge개 이하의 경로를 구하기 힘들다.
    // 중간 지점을 여러번 방문해도 되기 때문
    // 아마 pq가 폭발할거다.

    map<int, int> cache;
    while (1) {
        int pay = get<0>(pq.top());
        int edges = get<1>(pq.top());
        int u = get<2>(pq.top());
        pq.pop();

        if (cost[u] < pay) continue;
        if (u == dst) {
            if (edges > max_edge) continue;
            if (max_edge == INT_MAX) max_edge = edges;
            if (cache[edges] == 0) cache[edges] = pay;
        }

        for (P p : adj[u]) {
            int next_pay = pay + p.first, v = p.second;
            if (cost[v] > next_pay) {
                cost[v] = next_pay;
                pq.push({ next_pay,edges + 1,v });
            }
        }
    }
    
    return 0;
}