#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int MAX = 1001;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

bool visited[MAX][MAX];
bool hole[MAX][MAX];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int dx, dy, N; cin >> dx >> dy >> N;
    dx += 500, dy += 500;
    while (N--) {
        int x, y; cin >> x >> y;
        hole[x + 500][y + 500] = true;
    }

    queue<p> q;
    q.emplace(500, 500), q.emplace(-1, -1);
    visited[500][500] = true;

    int ans = 0;
    while (1) {
        auto [x, y] = q.front(); q.pop();
        if (x == -1) {
            ++ans; q.emplace(-1, -1);
            continue;
        }
        if (x == dx && y == dy) break;

        for (int i = 0; i < 4; ++i) {
            int X = x + mov[i][0], Y = y + mov[i][1];
            if (X < 0 || X>1000 || Y < 0 || Y>1000 || hole[X][Y] || visited[X][Y]) continue;
            visited[X][Y] = true;
            q.emplace(X, Y);
        }
    }
    cout << ans;
    return 0;
}