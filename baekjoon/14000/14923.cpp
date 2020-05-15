#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int bar = 1 << 10;
const int M = 1000;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

bool wall[M][M];
bool visited[M][M][2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, sr, sc, dr, dc;
    cin >> row >> col >> sr >> sc >> dr >> dc;
    --sr, --sc, --dr, --dc;
    loop(i, row) loop(j, col) cin >> wall[i][j];

    visited[0][0][0] = true;
    
    queue<int> q;
    q.emplace(sr * bar + sc);
    q.emplace(-1);

    int ans = 0;
    while (1) {
        int used = q.front(); q.pop();
        if (used == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans;
            q.emplace(-1);
            continue;
        }
        int c = used % bar; used /= bar;
        int r = used % bar; used /= bar;
        if (r == dr && c == dc) break;
        if (wall[r][c]) used = 1;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || visited[R][C][used]) continue;
            if (!wall[R][C] || !used) {
                visited[R][C][used] = true;
                q.emplace(used * bar * bar + R * bar + C);
            }
        }
    }
    cout << ans;
    return 0;
}