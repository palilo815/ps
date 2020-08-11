#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 1000;

int N, match[mx];
bool adj[mx][mx], visited[mx];

int dfs(int u) {
    visited[u] = true;
    loop(v, N) if (adj[u][v])
        if (match[v] == -1 || (!visited[match[v]] && dfs(match[v]))) {
            match[v] = u;
            return 1;
        }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(u, N) {
        int M; cin >> M;
        for (int v; M--;) {
            cin >> v;
            adj[u][v] = true;
        }
    }

    memset(match, -1, sizeof(int) * N);
    int ans = N;
    loop(i, N) {
        memset(visited, 0, N);
        ans -= dfs(i);
    }
    cout << ans;
    return 0;
}