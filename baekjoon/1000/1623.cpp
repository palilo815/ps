#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;

vector<int> adj[mxN], vt[2];
int dep[mxN], id[mxN], dp[mxN][2];

void dfs(int u, int d) {
    dep[u] = d;
    for (int& v : adj[u])
        dfs(v, d + 1);
}
void print(vector<int>& vt, int u, int in) {
    if (in) vt.emplace_back(u);
    for (int& v : adj[u])
        print(vt, v, !in && dp[v][1] > dp[v][0]);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> dp[i][1];
    for (int v = 1, p; v < N; ++v) {
        cin >> p;
        adj[--p].emplace_back(v);
    }

    dfs(0, 0);

    iota(id, id + N, 0);
    sort(id, id + N, [&](int& a, int& b) {
        return dep[a] > dep[b];
    });

    for (int i = 0; i < N; ++i) {
        int u = id[i];
        for (int& v : adj[u]) {
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }

    print(vt[1], 0, 1);
    print(vt[0], 0, 0);

    sort(vt[0].begin(), vt[0].end());
    sort(vt[1].begin(), vt[1].end());

    cout << dp[0][1] << ' ' << dp[0][0] << '\n';
    for (int& x : vt[1]) cout << x + 1 << ' ';
    cout << "-1\n";
    for (int& x : vt[0]) cout << x + 1 << ' ';
    cout << "-1\n";
    return 0;
}