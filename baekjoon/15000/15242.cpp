#include <bits/stdc++.h>
using namespace std;

const int mov[8][2] = { -2, -1, -2, 1, -1, -2, -1, 2, 1, -2, 1, 2, 2, -1, 2, 1};

int dist[8][8];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    char sr, sc, dr, dc; cin >> sr >> sc >> dr >> dc;
    sr -= 'a', sc -= '1';
    dr -= 'a', dc -= '1';

    queue<pair<int, int>> q;
    q.emplace((int)sr, (int)sc);
    dist[sr][sc] = 1;

    for (;;) {
        auto [r, c] = q.front(); q.pop();
        if (r == dr && c == dc) break;

        for (int i = 0; i < 8; ++i) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (0 <= R && R < 8 && 0 <= C && C < 8 && !dist[R][C]) {
                dist[R][C] = dist[r][c] + 1;
                q.emplace(R, C);
            }
        }
    }
    cout << dist[dr][dc] - 1;
    return 0;
}