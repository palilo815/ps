#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;
const int max_N = 100;
const int max_M = 10000;

vector<tup> adj[max_N + 1];
int dist[max_N + 1][max_M + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, T, M, L;
    cin >> N >> T >> M >> L;
    while (L--) {
        int u, v, t, m;
        cin >> u >> v >> t >> m;
        adj[u].push_back({ t,m,v });
        adj[v].push_back({ t,m,u });
    }

    // dist[idx][money] = idx 건물에 money를 사용해서 도달할 수 있는 최단거리
    for (int i = 1; i <= N; ++i)
        for (int j = 0; j <= M; ++j)
            dist[i][j] = INT_MAX;
    dist[1][0] = 0;

    priority_queue<tup, vector<tup>, greater<tup>>pq;
    pq.push({ 0,0,1 });
    while (!pq.empty()) {
        int time_u = get<0>(pq.top()), cost_u = get<1>(pq.top()), u = get<2>(pq.top()); pq.pop();

        // 도착지인 N에 도착하더라도 계속 탐색해야 한다.
        if (u == N || dist[u][cost_u] < time_u) continue;

        for (tup p : adj[u]) {
            int time_v = time_u + get<0>(p), cost_v = cost_u + get<1>(p);
            // time, money 제한이 걸리면 pass
            if (time_v > T || cost_v > M) continue;
            int v = get<2>(p);
            if (dist[v][cost_v] > time_v) {
                pq.push({ time_v,cost_v,v });
                dist[v][cost_v] = time_v;
            }
        }
    }

    // 찾은 경로 중 가장 돈을 덜 쓰는 방법을 출력한다.
    int ans = -1;
    for (int i = 0; i <= M; ++i)
        if (dist[N][i] != INT_MAX) {
            ans = i;
            break;
        }
    cout << ans;
    return 0;
}