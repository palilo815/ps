#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 182;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

int dist[mx][mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    queue<pair<int, int>> q;
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        if (c == '1') q.emplace(i, j), dist[i][j] = 1;
    }

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R ^ row && ~C && C ^ col && !dist[R][C]) {
                dist[R][C] = dist[r][c] + 1;
                q.emplace(R, C);
            }
        }
    }

    loop(i, row) {
        loop(j, col) cout << dist[i][j] - 1 << ' ';
        cout << '\n';
    }
    return 0;
}