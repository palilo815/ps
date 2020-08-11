#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 100;

bool wall[mx + 1][mx + 1];
int d1[mx][mx], d2[mx][mx];

vector<int> adj[mx * mx];
int match[mx * mx];
bool visited[mx * mx];

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

    int N, M; cin >> N >> M;
    for (int r, c; M--;) {
        cin >> r >> c;
        wall[r - 1][c - 1] = true;
    }
    loop(i, N + 1) wall[i][N] = true;
    loop(i, N + 1) wall[N][i] = true;

    int cnt1 = 0, cnt2 = 0;
    for (int k = N - 1; k != -N; --k, ++cnt1)
        for (int r = k >= 0 ? 0 : -k, c = r + k; r ^ N && c ^ N; ++r, ++c) {
            if (wall[r][c] && !wall[r + 1][c + 1]) ++cnt1;
            else if (!wall[r][c]) d1[r][c] = cnt1;
        }
    for (int k = 0; k <= (N - 1) << 1; ++k, ++cnt2)
        for (int r = k < N ? 0 : k - N + 1, c = k < N ? k : N - 1; r ^ N && ~c; ++r, --c) {
            if (wall[r][c] && c && !wall[r + 1][c - 1]) ++cnt2;
            else if (!wall[r][c]) d2[r][c] = cnt2;
        }

    loop(i, N) loop(j, N) if (!wall[i][j])
        adj[d1[i][j]].emplace_back(d2[i][j]);

    memset(match, -1, sizeof(int) * cnt2);
    int ans = 0;
    loop(i, cnt1) {
        memset(visited, 0, cnt1);
        ans += dfs(i);
    }
    cout << ans;
    return 0;
}