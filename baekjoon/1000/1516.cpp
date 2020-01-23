#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

// 짓는데 걸리는 시간, 선행 건물 개수, 완성된 시간
int cost[501], pre[501], ans[501];
vector<int> adj[501];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V;
    cin >> V;
    for (int i = 1; i <= V; ++i) {
        cin >> cost[i];
        int v;
        while (cin >> v) {
            if (v == -1) break;
            adj[v].push_back(i);
            pre[i]++;
        }
    }

    // 선행 건물이 없는 경우 pq에 넣어준다.
    priority_queue<P, vector<P>, greater<P>> pq;
    for (int i = 1; i <= V; ++i)
        if (!pre[i]) pq.push(make_pair(cost[i], i));

    while (!pq.empty()) {
        int T = pq.top().first, u = pq.top().second; pq.pop();
        ans[u] = T;
        loop(i, adj[u].size()) {
            int v = adj[u][i];
            --pre[v];
            // u를 지음으로써 v의 선행건물이 더이상 없어지면 pq에 넣어준다.
            if (!pre[v]) {
                int nextT = T + cost[v];
                pq.push(make_pair(nextT, v));
            }
        }
    }
    for (int i = 1; i <= V; ++i)
        cout << ans[i] << '\n';
    return 0;
}