#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> p;

const int max_N = 100000;

int height[max_N + 1];
vector<p> adj[max_N + 1];

ll dist_up[max_N + 1];
ll dist_dw[max_N + 1];

void Dijkstra(ll dist[], int src)
{
    priority_queue<p, vector<p>, greater<p>> pq;
    pq.push({ 0,src });
    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second; pq.pop();
        if (dist[u] < d) continue;

        for (p edge : adj[u]) {
            ll D = d + edge.first;
            int v = edge.second;
            if (height[u] >= height[v]) continue;
            if (dist[v] > D) {
                dist[v] = D;
                pq.push({ D,v });
            }
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, D, E;
    cin >> N >> M >> D >> E;

    for (int i = 1; i <= N; ++i)
        cin >> height[i];
    while (M--) {
        int u, v, d; cin >> u >> v >> d;
        adj[u].push_back({ d,v });
        adj[v].push_back({ d,u });
    }

    for (int i = 2; i < N; ++i)
        dist_up[i] = dist_dw[i] = INT64_MAX;

    // dist_up에는 1에서 출발해서 올라갈 때 최소거리
    // dist_dw에는 N에서 ...
    // dist_up + dist_dw이 총 거리다.
    Dijkstra(dist_up, 1);
    Dijkstra(dist_dw, N);

    // 올라가거나 내려가는 경로가 없으면 continue
    // 둘 다 있다면 가치를 계산해서 비교
    ll ans = INT64_MIN;
    for (int i = 2; i < N; ++i) {
        if (dist_up[i] == INT64_MAX || dist_dw[i] == INT64_MAX) continue;
        ans = max(ans, ll(height[i]) * E - D * (dist_up[i] + dist_dw[i]));
    }
    if (ans == INT64_MIN) cout << "Impossible";
    else cout << ans;
    return 0;
}