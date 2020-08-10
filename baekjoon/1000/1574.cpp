#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 300;

int R, C, match[mx];
bool adj[mx][mx], visited[mx];

int dfs(int u) {
    visited[u] = true;
    loop(v, C) if (adj[u][v])
        if (match[v] == -1 || (!visited[match[v]] && dfs(match[v]))) {
            match[v] = u;
            return 1;
        }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int K; cin >> R >> C >> K;
    loop(i, R) fill_n(adj[i], C, true);
    for (int r, c; K; --K) {
        cin >> r >> c;
        adj[r - 1][c - 1] = false;
    }

    memset(match, -1, sizeof(int) * C);
    int ans = 0;
    loop(i, R) {
        memset(visited, 0, R);
        ans += dfs(i);
    }
    cout << ans;
    return 0;
}