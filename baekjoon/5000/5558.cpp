#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e3;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

char mat[mxN][mxN + 1];
bool visited[mxN][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;
    loop(i, n) cin >> mat[i];

    vector<pair<int, int>> src(k + 1);
    loop(i, n) loop(j, m) {
        if (mat[i][j] == 'S') src[0] = {i, j};
        else if ('1' <= mat[i][j] && mat[i][j] <= '9')
            src[mat[i][j] - '0'] = {i, j};
    }

    auto bfs = [&](int s) {
        memset(visited, 0, sizeof(visited));
        queue<pair<int, int>> q;
        q.emplace(src[s]);
        q.emplace(-1, -1);

        for (int ret = 1;;) {
            auto [r, c] = q.front();
            q.pop();
            if (r == -1) {
                ++ret;
                q.emplace(-1, -1);
                continue;
            }

            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (~R && R != n && ~C && C != m && mat[R][C] != 'X' && !visited[R][C]) {
                    if (mat[R][C] == '1' + s) return ret;
                    visited[R][C] = true;
                    q.emplace(R, C);
                }
            }
        }
    };

    int ans = 0;
    for (int i = 0; i < k; ++i)
        ans += bfs(i);
    cout << ans;
}