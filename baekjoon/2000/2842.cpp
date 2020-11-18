#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 50;

int ord[mxN * mxN], h[mxN][mxN];
char mat[mxN][mxN];
bool visited[mxN][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    loop(i, N) loop(j, N) cin >> mat[i][j];
    loop(i, N) loop(j, N) cin >> h[i][j];

    loop(i, N) move(h[i], h[i] + N, ord + i * N);
    sort(ord, ord + N * N);
    int M = unique(ord, ord + N * N) - ord;

    int K = 0, sr, sc;
    loop(i, N) loop(j, N) if (mat[i][j] == 'K') K++;
    loop(i, N) loop(j, N) if (mat[i][j] == 'P') sr = i, sc = j;

    auto bfs = [&](int lo, int hi) {
        if (hi < h[sr][sc] || h[sr][sc] < lo) return false;

        queue<pair<int, int>> q;
        q.emplace(sr, sc);

        memset(visited, 0, sizeof(visited));
        visited[sr][sc] = true;

        int cnt = 0;
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            if (mat[r][c] == 'K' && ++cnt == K) return true;

            for (int R = r - 1; R <= r + 1; ++R)
                for (int C = c - 1; C <= c + 1; ++C) {
                    if (~R && R != N && ~C && C != N && !visited[R][C] && lo <= h[R][C] && h[R][C] <= hi) {
                        visited[R][C] = true;
                        q.emplace(R, C);
                    }
                }
        }
        return false;
    };

    int ans = INT_MAX;
    for (int l = 0, r = 0; r < M;) {
        if (bfs(ord[l], ord[r])) {
            ans = min(ans, ord[r] - ord[l]);
            if (l == r) break;
            ++l;
        } else
            ++r;
    }
    cout << ans;
}