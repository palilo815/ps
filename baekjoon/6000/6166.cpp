#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int MAX = 303;
const int safe = 0x3f3f3f3f;

int T[MAX][MAX];
bool visited[MAX][MAX];

bool is_out(int x, int y) {
    return x < 0 || x >= MAX || y < 0 || y >= MAX;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    memset(T, 0x3f, sizeof(T));
    int M; cin >> M;
    while (M--) {
        int x, y, t; cin >> x >> y >> t;
        T[x][y] = min(T[x][y], t);
        loop(i, 4) {
            int X = x + mov[i][0], Y = y + mov[i][1];
            if (!is_out(X, Y)) T[X][Y] = min(T[X][Y], t);
        }
    }
    if (T[0][0] == 0) { cout << -1; return 0; }
    visited[0][0] = true;

    queue<pair<int, int>> q;
    q.emplace(0, 0), q.emplace(-1, -1);

    int ans = 0;
    while (1) {
        auto [x, y] = q.front(); q.pop();
        if (x == -1) {
            if (q.empty()) {
                ans = -1; break;
            }
            ++ans; q.emplace(-1, -1);
            continue;
        }
        if (T[x][y] == safe) break;

        loop(i, 4) {
            int X = x + mov[i][0], Y = y + mov[i][1];
            if (is_out(X, Y) || visited[X][Y] || T[X][Y] <= ans + 1) continue;
            visited[X][Y] = true;
            q.emplace(X, Y);
        }
    }
    cout << ans;
    return 0;
}