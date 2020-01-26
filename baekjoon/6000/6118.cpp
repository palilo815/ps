#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

int dist[20001];
vector<int> graph[20001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 20001) dist[i] = INT32_MAX;
    int V, E; cin >> V >> E;
    while (E--) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0,1 });
    dist[1] = 0;
    while (!pq.empty()) {
        int cost = pq.top().first, here = pq.top().second; pq.pop();
        if (dist[here] < cost) continue;
        for (int there : graph[here])
            if (dist[there] > cost + 1) {
                dist[there] = cost + 1;
                pq.push({ cost + 1, there });
            }
    }

    int ans = 0, MAX = 0, cnt = 0;
    for (int i = 2; i <= V; ++i) {
        // 더 먼 지점을 발견하면
        // MAX = 그 거리, ans = 번호, cnt = 1
        if (dist[i] > MAX) {
            MAX = dist[i];
            ans = i;
            cnt = 1;
        }
        // 가장 먼 지점을 추가로 발견하면
        // cnt += 1
        else if (dist[i] == MAX)
            ++cnt;
    }
    // 번호, 거리, 개수 출력
    cout << ans << ' ' << MAX << ' ' << cnt;
    return 0;
}