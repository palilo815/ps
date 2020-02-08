#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 50000;

int cost[max_N + 1];
vector<p> adj[max_N + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    for (int i = 2; i <= N; ++i)
        cost[i] = INT_MAX;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.push({ 0,1 });
    while (1) {
        auto [c, u] = pq.top(); pq.pop();
        if (u == N) break;
        if (cost[u] < c) continue;
        for (auto [w, v] : adj[u])
            if (cost[v] > c + w) {
                cost[v] = c + w;
                pq.push({ c + w,v });
            }
    }
    cout << cost[N];
    return 0;
}