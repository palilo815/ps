#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
const int max_N = 50000;

vector<p> adj[max_N + 1];
map<int,int> dist[max_N + 1];
int max_dist(int parent, int u)
{
    int ret = 0;
    for (p edge : adj[u]) {
        int w = edge.first, v = edge.second;
        if (v == parent) continue;

        // u->v로 갈 때 최대거리를 구해놨다면 그대로 사용하면 되고
        // 안구해놨다면 map에 추가해준다.
        auto it = dist[u].find(v);
        if (it == dist[u].end()) {
            int tmp = w + max_dist(u, v);
            ret = max(ret, tmp);
            dist[u][v] = tmp;
        }
        else
            ret = max(ret, it->second);
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    for (int i = 1; i <= N; ++i)
        cout << max_dist(-1, i) << '\n';
    return 0;
}