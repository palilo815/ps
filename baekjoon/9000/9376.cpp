#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int M = 102;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int row, col;
char prison[M][M];
int dist[3][M][M];
deque<p> dq;

void BFS(int sr, int sc, int dist[][M]) {
    dist[sr][sc] = 0;
    dq.emplace_back(sr, sc);

    while (!dq.empty()) {
        auto [r, c] = dq.front(); dq.pop_front();
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R > row + 1 || C < 0 || C > col + 1 || dist[R][C] != -1 || prison[R][C] == '*')
                continue;
            if (prison[R][C] == '#') {
                dist[R][C] = dist[r][c] + 1;
                dq.emplace_back(R, C);
            }
            else {
                dist[R][C] = dist[r][c];
                dq.emplace_front(R, C);
            }
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        cin >> row >> col;
        int cr1 = 0, cc1 = 0, cr2 = 0, cc2 = 0;
        loop(i, row + 2) loop(j, col + 2) {
            if (i == 0 || i == row + 1 || j == 0 || j == col + 1)
                prison[i][j] = '.';
            else {
                cin >> prison[i][j];
                if (prison[i][j] == '$')
                    cr1 ? (cr2 = i, cc2 = j) : (cr1 = i, cc1 = j);
            }
        }

        memset(dist, -1, sizeof(dist));

        BFS(0, 0, dist[0]);
        BFS(cr1, cc1, dist[1]);
        BFS(cr2, cc2, dist[2]);

        int ans = INT_MAX;
        loop(i, row + 2) loop(j, col + 2) if (prison[i][j] != '*') {
            int tmp = 0;
            loop(k, 3) tmp += dist[k][i][j];
            if (prison[i][j] == '#') tmp -= 2;
            ans = min(ans, tmp);
        }
        cout << ans << '\n';
    }
    return 0;
}