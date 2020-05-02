#include <bits/stdc++.h>
using namespace std;

const int max_N = 50001;

vector<int> adj[max_N];
bool visited[max_N][2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    int turn = 1;
    visited[1][0] = true;

    queue<int> q;
    q.emplace(1), q.emplace(0);
    while (1) {
        int u = q.front(); q.pop();
        if (!u) {
            if (q.empty()) break;
            turn ^= 1; q.emplace(0);
            continue;
        }

        for (int v : adj[u]) if (!visited[v][turn]) {
            visited[v][turn] = true;
            q.emplace(v);
        }
    }

    long long odd = 0, even = 0;
    for (int i = 1; i <= N; ++i) {
        if (visited[i][0] && !visited[i][1])
            ++even;
        else if (visited[i][1] && !visited[i][0])
            ++odd;
    }
    cout << odd * even * 2;
    return 0;
}