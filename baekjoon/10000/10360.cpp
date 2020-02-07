#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

vector<p> adj[max_N + 1];
bool in_slope[max_N + 1];
int awesome[max_N + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ w,v });
        in_slope[v] = true;
    }

    priority_queue<p> pq;
    for (int i = 1; i <= N; ++i)
        awesome[i] = INT_MIN;
    for (int i = 1; i <= N; ++i)
        if (!in_slope[i])
            pq.push({ 0,i });

    while (!pq.empty()) {
        int u = pq.top().second, val = pq.top().first; pq.pop();
        if (awesome[u] > val) continue;
        for (p edge : adj[u]) {
            int v = edge.second, w = val + edge.first;
            if (awesome[v] < w) {
                awesome[v] = w;
                pq.push({ w,v });
            }
        }
    }

    int ans = INT_MIN;
    for (int i = 1; i <= N; ++i)
        ans = max(ans, awesome[i]);
    cout << ans;
    return 0;
}