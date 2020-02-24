#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 5000;

vector<p> adj[max_N + 1];
int dist[max_N + 1];

auto cmp = [](const tup& a, const tup& b) {
    auto [a1, a2, a3] = a;
    auto [b1, b2, b3] = b;
    return a1 - a2 > b1 - b2;
};
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    /*
       find min_distance except one edge!!!!
    */
    int N, M; cin >> N >> M;
    int sum = 0;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        sum += w;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    int src, dst; cin >> src >> dst;
    fill(dist, dist + N + 1, INT_MAX);
    dist[src] = 0;

    priority_queue<tup, vector<tup>, decltype(cmp)> pq(cmp);
    pq.push({ 0,0,src });
    while (!pq.empty()) {
        auto [d, max_w, u] = pq.top(); pq.pop();
        if (dist[u] < d - max_w) continue;
        for (auto [w, v] : adj[u]) {
            int D = d + w, new_w = max(w, max_w);
            if (dist[v] > D - new_w) {
                dist[v] = D - new_w;
                pq.push({ D,new_w,v });
            }
        }
    }
    cout << sum - dist[dst];
    return 0;
}