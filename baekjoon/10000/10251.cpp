#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 100;
const int INF = 0x3f3f3f3f;

int cost[M][M][2];
int DP[M + 1][M + 1][2][M * 2 + 1];
// DP[i][j][d][t] : (i,j)위치, 방향 d, t번 turn했을 때 가스 사용량

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        int R, C, L, G;
        cin >> R >> C >> L >> G;
        loop(i, R) loop(j, C - 1)
            cin >> cost[i][j][0];
        loop(i, R - 1) loop(j, C)
            cin >> cost[i][j][1];

        int max_turn = min(R, C) * 2 + 1;
        loop(i, R) loop(j, C)
            memset(DP[i][j][0], 0x3f, sizeof(int) * max_turn),
            memset(DP[i][j][1], 0x3f, sizeof(int) * max_turn);
        DP[0][0][0][0] = DP[0][0][1][0] = 0;

#define CURR DP[i][j][d][t]
#define EAST DP[i][j+1][0][t+(d!=0)]
#define DOWN DP[i+1][j][1][t+(d!=1)]

        loop(i, R) loop(j, C) loop(d, 2) loop(t, max_turn)
            if (CURR != INF) {
                if (CURR + cost[i][j][0] <= G)
                    EAST = min(EAST, CURR + cost[i][j][0]);
                if (CURR + cost[i][j][1] <= G)
                    DOWN = min(DOWN, CURR + cost[i][j][1]);
            }

        int ans = -1;
        loop(t, max_turn)
            if (DP[R - 1][C - 1][0][t] != INF || DP[R - 1][C - 1][1][t] != INF) {
                ans = (R + C - 2) * L + t;
                break;
            }
        cout << ans << '\n';
    }
    return 0;
}