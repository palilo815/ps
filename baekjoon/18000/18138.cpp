#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 200;

int a[mx], b[mx], adj[mx][4], match[mx];
bool visited[mx];

int dfs(int u) {
    visited[u] = true;
    for (int v = adj[u][0]; v ^ adj[u][1]; ++v)
        if (match[v] == -1 || (!visited[match[v]] && dfs(match[v]))) {
            match[v] = u;
            return 1;
        }
    for (int v = adj[u][2]; v ^ adj[u][3]; ++v)
        if (match[v] == -1 || (!visited[match[v]] && dfs(match[v]))) {
            match[v] = u;
            return 1;
        }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, N) cin >> a[i];
    loop(i, M) cin >> b[i];

    loop(i, M) b[i] <<= 2;
    sort(b, b + M);

    loop(i, N) {
        adj[i][0] = lower_bound(b, b + M, a[i] * 2) - b;
        adj[i][1] = upper_bound(b, b + M, a[i] * 3) - b;
        adj[i][2] = lower_bound(b, b + M, a[i] * 4) - b;
        adj[i][3] = upper_bound(b, b + M, a[i] * 5) - b;
    }

    memset(match, -1, sizeof(int) * M);
    int ans = 0;
    loop(i, N) {
        memset(visited, 0, N);
        ans += dfs(i);
    }
    cout << ans;
    return 0;
}