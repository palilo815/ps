#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
using ll = long long;

const int mx = 30;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

bool wall[mx][mx];
int jump[mx][mx];
ll dist[mx][mx];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int W, H, G, E;
    for (;;) {
        cin >> W >> H;
        if (!W) break;

        memset(wall, 0, sizeof(wall));
        memset(jump, 0, sizeof(jump));
        memset(dist, 0x3f, sizeof(dist));

        cin >> G;
        for (int c, r; G--;) {
            cin >> c >> r;
            wall[r][c] = true;
        }

        cin >> E;
        for (int c1, r1, c2, r2, t; E--;) {
            cin >> c1 >> r1 >> c2 >> r2 >> t;
            jump[r1][c1] = t << 10 | r2 << 5 | c2;
        }

        dist[0][0] = 0;
        bool update;
        for (int cnt = H * W; cnt--;) {
            update = false;
            loop(r, H) loop(c, W) if (dist[r][c] != INF) {
                if (r == H - 1 && c == W - 1) continue;
                if (jump[r][c]) {
                    int t = jump[r][c] >> 10;
                    int R = jump[r][c] >> 5 & 31;
                    int C = jump[r][c] & 31;
                    if (dist[R][C] > dist[r][c] + t)
                        dist[R][C] = dist[r][c] + t, update = true;
                } else
                    loop(i, 4) {
                        int R = r + mov[i][0], C = c + mov[i][1];
                        if (~R && R != H && ~C && C != W && !wall[R][C] && dist[R][C] > dist[r][c] + 1)
                            dist[R][C] = dist[r][c] + 1, update = true;
                    }
            }
            if (!update) break;
        }

        if (update)
            cout << "Never\n";
        else if (dist[H - 1][W - 1] == INF)
            cout << "Impossible\n";
        else
            cout << dist[H - 1][W - 1] << '\n';
    }
    return 0;
}