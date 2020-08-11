#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 100;

vector<int> adj[mx];
int match[mx];
bool visited[mx];

int dfs(int u) {
    visited[u] = true;
    for (int& v : adj[u])
        if (match[v] == -1 || (!visited[match[v]] && dfs(match[v]))) {
            match[v] = u;
            return 1;
        }
    return 0;
}
void solve() {
    int R, C, N; cin >> R >> C >> N;
    loop(i, R) adj[i].clear();
    for (int r, c; N--;) {
        double a, b; cin >> a >> b;
        r = a, c = b;
        adj[r].emplace_back(c);
    }

    memset(match, -1, sizeof(int) * C);
    int ans = 0;
    loop(i, R) {
        memset(visited, 0, R);
        ans += dfs(i);
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}