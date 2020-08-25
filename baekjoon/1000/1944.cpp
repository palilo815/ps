#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int mxN = 50;
const int INF = 0x3f3f3f3f;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mxN + 2][mxN + 2];
int new_d[mxN + 2][mxN + 2];

void bfs(p s) {
    queue<p> q;
    q.emplace(s);

    memset(new_d, 0x3f, sizeof(new_d));
    new_d[s.first][s.second] = 0;

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~mat[R][C] && new_d[R][C] > new_d[r][c] + 1) {
                new_d[R][C] = new_d[r][c] + 1;
                q.emplace(R, C);
            }
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;

    ++M;
    vector<p> vtx;
    vector<bool> conn(M);
    vector<int> dist(M, INF);
    dist[0] = 0;

    memset(mat[0], -1, N + 2);
    for (int i = 1; i <= N; ++i)
        mat[i][0] = mat[i][N + 1] = -1;
    memset(mat[N + 1], -1, N + 2);

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j) {
            char c; cin >> c;
            if (c == 'S' || c == 'K')
                vtx.emplace_back(i, j);
            else if (c == '1') mat[i][j] = -1;
        }

    int ans = 0;
    loop(_, M) {
        int k = -1;
        loop(i, M) if (!conn[i] && (k == -1 || dist[i] < dist[k]))
            k = i;

        if (dist[k] == INF) {ans = -1; break;}
        ans += dist[k];
        conn[k] = true;

        bfs(vtx[k]);

        loop(i, M) if (!conn[i] && new_d[vtx[i].first][vtx[i].second] < dist[i])
            dist[i] = new_d[vtx[i].first][vtx[i].second];

    }
    cout << ans;
    return 0;
}