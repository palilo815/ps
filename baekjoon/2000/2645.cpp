#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
using p = pair<int, int>;

const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};
const int max_N = 51;
const int bar = 64;

bool pos[max_N][max_N];
int cost[max_N][max_N];
int dir[max_N][max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, sx, sy, ex, ey, k, M;
    cin >> N >> sx >> sy >> ex >> ey >> k >> M;

    while (M--) {
        int cnt, x, y, X, Y;
        cin >> cnt >> x >> y;
        while (--cnt) {
            cin >> X >> Y;
            int dx = X < x ? -1 : (x < X);
            int dy = Y < y ? -1 : (y < Y);
            for (; x != X || y != Y; x += dx, y += dy)
                pos[x][y] = true;
        }
        pos[x][y] = true;
    }

    dir[sx][sy] = -1;
    memset(cost, 0x3f, sizeof(cost));
    cost[sx][sy] = pos[sx][sy] ? k : 1;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(cost[sx][sy], sx * bar + sy);

    int ans;
    while (1) {
        auto [c, x] = pq.top(); pq.pop();
        int y = x % bar; x /= bar;
        if (x == ex && y == ey) {
            ans = c;
            break;
        }

        loop(i, 4) {
            int X = x + mov[i][0], Y = y + mov[i][1];
            if (X < 1 || X > N || Y < 1 || Y > N) continue;
            int C = c + (pos[X][Y] ? k : 1);
            if (cost[X][Y] > C) {
                cost[X][Y] = C;
                dir[X][Y] = i;
                pq.emplace(C, X * bar + Y);
            }
        }
    }

    stack<p> stk;
    int d = -1;
    while (1) {
        if (d != dir[ex][ey]) {
            d = dir[ex][ey];
            stk.emplace(ex, ey);
        }
        if (d == -1) break;
        ex += mov[3 - d][0], ey += mov[3 - d][1];
    }
    cout << ans << '\n' << stk.size();
    while (!stk.empty()) {
        cout << ' ' << stk.top().first << ' ' << stk.top().second;
        stk.pop();
    }
    return 0;
}