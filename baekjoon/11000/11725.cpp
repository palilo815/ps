#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

vector<int> adj[mxN + 1];
int par[mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    par[1] = -1;

    queue<int> q;
    q.emplace(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int& v : adj[u])
            if (!par[v]) {
                par[v] = u;
                q.emplace(v);
            }
    }

    for (int i = 2; i <= N; ++i)
        cout << par[i] << '\n';
}