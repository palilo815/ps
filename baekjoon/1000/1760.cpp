#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 100;

char mat[mx][mx];
int row[mx][mx], col[mx][mx], match[mx * mx];
bool visited[mx * mx];
vector<int> adj[mx * mx];

int dfs(int u) {
    visited[u] = true;
    for (int& v : adj[u])
        if (match[v] == -1 || (!visited[match[v]] && dfs(match[v]))) {
            match[v] = u;
            return 1;
        }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int R, C; cin >> R >> C;
    loop(i, R) loop(j, C) cin >> mat[i][j];

    int cnt_R = 0, cnt_C = 0;
    loop(i, R) loop(j, C) if (mat[i][j] != '2') {
        while (j < C && mat[i][j] != '2')
            row[i][j++] = cnt_R;
        ++cnt_R;
    }
    loop(j, C) loop(i, R) if (mat[i][j] != '2') {
        while (i < R && mat[i][j] != '2')
            col[i++][j] = cnt_C;
        ++cnt_C;
    }

    loop(i, R) loop(j, C) if (mat[i][j] == '0')
        adj[row[i][j]].emplace_back(col[i][j]);

    memset(match, -1, sizeof(int) * cnt_C);
    int ans = 0;
    loop(i, cnt_R) {
        memset(visited, 0, cnt_R);
        ans += dfs(i);
    }
    cout << ans;
    return 0;
}