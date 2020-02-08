#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 200;

int table[max_N + 1][max_N + 1];
int dist[max_N + 1];
vector<p> adj[max_N + 1];

void Dijkstra(int src, int N)
{
    vector<int> parent(N + 1);
    LOOP(i, N) dist[i] = INT_MAX;
    dist[src] = 0;
    priority_queue<p, vector<p>, greater<p>> pq;
    pq.push({ 0,src });
    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second; pq.pop();
        if (dist[u] < d) continue;

        for (p edge : adj[u]) {
            int D = d + edge.first, v = edge.second;
            if (dist[v] > D) {
                dist[v] = D;
                parent[v] = u;
                pq.push({ D,v });
            }
        }
    }

    // table 만드는 과정인데, 더 간편한 과정이 있을듯
    bool update = true;
    while (update) {
        update = false;
        LOOP(i, N) if (parent[i]) {
            if (parent[i] == src) {
                table[src][i] = i;
                update = true;
                parent[i] = 0;
            }
            else if (table[src][parent[i]]) {
                table[src][i] = table[src][parent[i]];
                update = true;
                parent[i] = 0;
            }
        }
    }
}
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
    LOOP(i, N) Dijkstra(i, N);
    LOOP(i, N) {
        LOOP(j, N) {
            if (i == j) cout << '-';
            else cout << table[i][j];
            cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}