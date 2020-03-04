#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 1000;

int cost[max_N + 1];
int dist[max_N + 1][max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) cin >> cost[i];

    fill(&dist[0][0], &dist[N + 1][0], INT_MAX);
    dist[2][1] = cost[2];

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(dist[2][1], 1, 2);
    while (1) {
        auto [d, jump, u] = pq.top(); pq.pop();
        if (dist[u][jump] < d) continue;
        if (u == N) { cout << d; break; }

        int v;
        v = u - jump;
        if (v > 0 && dist[v][jump] > d + cost[v]) {
            dist[v][jump] = d + cost[v];
            pq.emplace(d + cost[v], jump, v);
        }
        v = u + jump + 1, ++jump;
        if (v <= N && dist[v][jump] > d + cost[v]) {
            dist[v][jump] = d + cost[v];
            pq.emplace(d + cost[v], jump, v);
        }
    }
    return 0;
}