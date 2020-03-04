#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 10000;
const int max_P = 10;

vector<p> adj[max_N + 1];
vector<p> trap[2][max_N + 1];

bool swch[max_N + 1];
int dist[max_N + 1][2][max_P];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K, L, P; cin >> N >> M >> K >> L >> P;
    while (K--) {
        int idx; cin >> idx;
        swch[idx] = true;
    }
    for (int i = 0; i < M - L; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
    }
    while (L--) {
        int u, v, w; cin >> u >> v >> w;
        trap[0][u].emplace_back(w, v);
        trap[1][v].emplace_back(w, u);
    }
    int src, dst; cin >> src >> dst;

    fill(&dist[0][0][0], &dist[N + 1][0][0], INT_MAX);
    dist[src][0][0] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 0, src);
    while (!pq.empty()) {
        auto [d, cnt, u] = pq.top(); pq.pop();
        int flag = cnt / P % 2, rem = cnt % P;
        if (dist[u][flag][rem] < d) continue;
        if (u == dst) { cout << d; return 0; }

        if (swch[u]) { ++cnt, flag = cnt / P % 2, rem = (rem + 1) % P; }
        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v][flag][rem] > D) {
                dist[v][flag][rem] = D;
                pq.emplace(D, cnt, v);
            }
        }
        for (auto [w, v] : trap[flag][u]) {
            int D = d + w;
            if (dist[v][flag][rem] > D) {
                dist[v][flag][rem] = D;
                pq.emplace(D, cnt, v);
            }
        }
    }
    cout << -1;
    return 0;
}