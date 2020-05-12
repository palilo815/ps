#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 401;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int mod = 1000000007;

bool wall[M][M];
int cnt[M][M];

int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int sx, sy, T, dx, dy, N;
    cin >> sx >> sy >> T >> dx >> dy >> N;
    
    int f_x = 200 - sx, f_y = 200 - sy;
    dx += f_x, dy += f_y;
    if (dist(dx, dy, 200, 200) > T) {
        cout << 0;
        return 0;
    }

    while (N--) {
        int x, y; cin >> x >> y;
        x += f_x, y += f_y;
        if (x < 0 || x > 400 || y < 0 || y > 400) continue;
        wall[x][y] = true;
    }

    queue<pair<int, int>> q;
    q.emplace(200, 200), q.emplace(-1, -1);
    cnt[200][200] = 1;

    int ans = 0;
    while (1) {
        auto [x, y] = q.front(); q.pop();
        if (x == -1) {
            if (q.empty() || !(T--)) break;
            q.emplace(-1, -1);
            continue;
        }

        loop(i, 4) {
            int X = x + mov[i][0], Y = y + mov[i][1];
            if (wall[X][Y] || dist(X, Y, dx, dy) >= T) continue;
            if (X == dx && Y == dy) ans = (ans + cnt[x][y]) % mod;
            else {
                if (!cnt[X][Y]) q.emplace(X, Y);
                cnt[X][Y] = (cnt[X][Y] + cnt[x][y]) % mod;
            }
        }
        cnt[x][y] = 0;
    }
    cout << ans;
    return 0;
}