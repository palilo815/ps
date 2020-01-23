#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

int graph[1001][1001], cache[1001], dist[1001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** initialize ** 
    memset(graph, -1, sizeof(graph));
    loop(i, 1001) dist[i] = INT_MAX;
    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        if (graph[u][v] == -1) graph[u][v] = w;
        else graph[u][v] = min(graph[u][v], w);
    }

    // u에서 v로 가는 경로
    int u, v; cin >> u >> v;
    cache[u] = -1, dist[u] = 0;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0,u });

    while (1) {
        int cost = pq.top().first, curr = pq.top().second; pq.pop();
        if (curr == v) break;
        loop(i, 1001)
            if (graph[curr][i] != -1) {
                int next_cost = cost + graph[curr][i];
                if (next_cost < dist[i]) {
                    dist[i] = next_cost;
                    cache[i] = curr;
                    pq.push({ next_cost,i });
                }
            }
    }
    cout << dist[v] << '\n';

    // cache[i]에는 i 이전에 방문한 도시의 번호가 들어있다.
    // cache[u] = -1을 넣어놓은 상태
    stack<int> stk;
    while (v != -1) {
        stk.push(v);
        v = cache[v];
    }

    // 정답 역추적
    cout << stk.size() << '\n';
    while (!stk.empty()) {
        cout << stk.top() << ' ';
        stk.pop();
    }
    return 0;
}