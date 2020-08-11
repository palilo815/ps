#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 50;

bool adj[mx][mx];
int N, x[mx], y[mx], z[mx];

int match[mx];
bool visited[mx];

bool dfs(int u) {
    visited[u] = true;
    loop(v, N) if (adj[u][v])
        if (match[v] == -1 || (!visited[match[v]] && dfs(match[v]))) {
            match[v] = u;
            return true;
        }
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> x[i] >> y[i] >> z[i];

    loop(i, N) loop(j, N) if (i ^ j)
        adj[i][j] = (x[i] >= x[j] && y[i] >= y[j] && z[i] >= z[j]);
    loop(i, N) loop(j, i) if (adj[i][j] && adj[j][i])
        adj[i][j] = false;

    memset(match, -1, sizeof(int) * N);
    int ans = N;
    loop(i, N) {
        memset(visited, 0, N);
        if (dfs(i)) {
            --ans;
            memset(visited, 0, N);
            if (dfs(i)) --ans;
        }
    }
    cout << ans;
    return 0;
}