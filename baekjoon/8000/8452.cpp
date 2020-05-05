#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 1001;
const int max_M = 100000;
const int max_Q = 200000;
const int INF = 0x3f3f3f3f;

vector<int> adj[max_N];
p edge[max_M];
int query[max_Q];

int dist[max_N];
queue<int> q;

void BFS(int src) {
    q.emplace(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u])
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.emplace(v);
            }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, Q; cin >> N >> M >> Q;
    loop(i, M) cin >> edge[i].first >> edge[i].second;
    loop(i, Q) {
        char q; int x; cin >> q >> x;
        if (q == 'E') query[i] = x;
        else {
            edge[x - 1].first *= -1;
            edge[x - 1].second *= -1;
            query[i] = -x;
        }
    }

    loop(i, M) if (edge[i].first > 0)
        adj[edge[i].first].emplace_back(edge[i].second);

    memset(dist + 1, 0x3f, sizeof(int)* N);
    dist[1] = 0;

    BFS(1);

    stack<int> ans;
    for (int i = Q - 1; i >= 0; --i) {
        if (query[i] > 0)
            ans.emplace(dist[query[i]] == INF ? -1 : dist[query[i]]);
        else {
            auto& [u, v] = edge[-query[i] - 1];
            u = -u, v = -v;
            adj[u].emplace_back(v);
            BFS(u);
        }
    }

    while (!ans.empty()) {
        cout << ans.top() << '\n';
        ans.pop();
    }
    return 0;
}