#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 1000;
const int max_K = 10;
const int bar = 1 << 10;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

bool wall[M][M];
int visited[M][M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, K; cin >> row >> col >> K;
    loop(i, row) loop(j, col) {
        char x; cin >> x;
        if (x == '1') wall[i][j] = true;
    }

    queue<int> q;
    q.emplace((K + 1)* bar* bar), q.emplace(-1);

    visited[0][0] = K + 1;
    int ans = 1;

    while (1) {
        int crash = q.front(); q.pop();
        if (crash == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans;
            q.emplace(-1);
            continue;
        }
        if (!(ans % 2)) q.emplace(crash);

        int c = crash % bar; crash /= bar;
        int r = crash % bar; crash /= bar;
        if (r == row - 1 && c == col - 1) break;
        
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col) continue;
            if (wall[R][C] && !(ans % 2)) continue;

            int CRASH = wall[R][C] ? crash - 1 : crash;
            if (visited[R][C] < CRASH) {
                visited[R][C] = CRASH;
                q.emplace(CRASH * bar * bar + R * bar + C);
            }
        }
    }
    cout << ans;
    return 0;
}