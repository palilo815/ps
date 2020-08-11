#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 100;

char mat[mx + 1][mx + 1];
int row[mx][mx], col[mx][mx];

vector<int> adj[mx * mx / 2];
int match[mx * mx / 2];
bool visited[mx * mx / 2];

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

    int N; cin >> N;
    loop(i, N) cin >> mat[i];

    int cnt_R = 0, cnt_C = 0;
    loop(i, N) loop(j, N) if (mat[i][j] == '.') {
        while (mat[i][j] == '.')
            row[i][j++] = cnt_R;
        ++cnt_R;
    }
    loop(j, N) loop(i, N) if (mat[i][j] == '.') {
        while (mat[i][j] == '.')
            col[i++][j] = cnt_C;
        ++cnt_C;
    }

    loop(i, N) loop(j, N) if (mat[i][j] == '.')
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