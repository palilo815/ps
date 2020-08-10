#include <bits/stdc++.h>
using namespace std;

const int mx = 501;

vector<int> adj[mx];
bool visited[mx];
int match[mx];

int dfs(int u) {
    visited[u] = true;
    for (int& v : adj[u])
        if (!match[v] || (!visited[match[v]] && dfs(match[v]))) {
            match[v] = u;
            return 1;
        }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    for (int r, c; K; --K) {
        cin >> r >> c;
        adj[r].emplace_back(c);
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        memset(visited + 1, 0, N);
        ans += dfs(i);
    }
    cout << ans;
    return 0;
}