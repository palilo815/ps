#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int, int> tup;

const int max_N = 10001;

vector<tup> adj[max_N];
vector<tup> rev[max_N];
int d1[max_N], d2[max_N];
int p1[max_N], p2[max_N];
int complaint[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for(int i = 1; i <= M; ++i) {
        int u, v, w1, w2; cin >> u >> v >> w1 >> w2;
        adj[u].emplace_back(v, w1, w2, i);
        rev[v].emplace_back(u, w1, w2, i);
    }

    priority_queue<p, vector<p>, greater<p>> pq;

    memset(d1 + 1, 0x3f, sizeof(int) * N);
    d1[N] = 0;

    pq.emplace(0, N);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d1[u] < d) continue;

        for (auto [v, w1, w2, i] : rev[u]) {
            int D = d + w1;
            if (d1[v] > D) {
                d1[v] = D, p1[v] = i;
                pq.emplace(D, v);
            }
        }
    }

    memset(d2 + 1, 0x3f, sizeof(int) * N);
    d2[N] = 0;

    pq.emplace(0, N);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d2[u] < d) continue;

        for (auto [v, w1, w2, i] : rev[u]) {
            int D = d + w2;
            if (d2[v] > D) {
                d2[v] = D, p2[v] = i;
                pq.emplace(D, v);
            }
        }
    }

    memset(complaint + 1, 0x3f, sizeof(int) * N);
    complaint[1] = 0;

    pq.emplace(0, 1);
    while (1) {
        auto [c, u] = pq.top(); pq.pop();
        if (complaint[u] < c) continue;
        if (u == N) { cout << c; break; }

        for (auto [v, w1, w2, i] : adj[u]) {
            int C = c + (p1[u] != i) + (p2[u] != i);
            if (complaint[v] > C) {
                complaint[v] = C;
                pq.emplace(C, v);
            }
        }
    }
    return 0;
}