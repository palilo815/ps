#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 20;

int dist[max_N];
p adj[max_N][max_N];

auto cmp = [](const pair<p, int>& a, const pair<p, int>& b) {
    auto [a1, a2] = a.first;
    auto [b1, b2] = b.first;
    return a1 * a2 > b1 * b2;
};
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) {
        char w; cin >> w;
        if (w != '.') adj[i][j].first = w - '0';
    }
    loop(i, N) loop(j, N) {
        char w; cin >> w;
        if (w != '.') adj[i][j].second = w - '0';
    }

    fill(dist + 1, dist + N, INT_MAX);

    priority_queue<pair<p, int>, vector<pair<p, int>>, decltype(cmp)> pq(cmp);
    pq.push({ {0,0},0 });
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        auto [w1, w2] = w;

        if (dist[u] < w1 * w2) continue;
        if (u == 1) break;

        loop(v, N) if (adj[u][v].first) {
            auto [W1, W2] = adj[u][v];
            int nxt_dist = (w1 + W1) * (w2 + W2);
            if (dist[v] > nxt_dist) {
                dist[v] = nxt_dist;
                pq.push({ make_pair(w1 + W1, w2 + W2), v });
            }
        }
    }
    int ans = dist[1];
    cout << (ans == INT_MAX ? -1 : ans);
    return 0;
}