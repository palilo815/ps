#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int M = 100;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int castle[M][M];
bool visited[M][M][2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, T;
    cin >> row >> col >> T;
    loop(i, row) loop(j, col)
        cin >> castle[i][j];

    visited[0][0][0] = true;
    
    queue<tup> q;
    q.emplace(0, 0, 0);
    q.emplace(-1, -1, -1);

    int ans = 0;
    while (1) {
        auto [r, c, sword] = q.front(); q.pop();
        if (r == -1) {
            if (q.empty() || ++ans > T) {
                ans = -1;
                break;
            }
            q.emplace(-1, -1, -1);
            continue;
        }
        if (r == row - 1 && c == col - 1) break;
        if (castle[r][c] == 2) sword = 1;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || visited[R][C][sword]) continue;
            if (castle[R][C] != 1 || sword) {
                visited[R][C][sword] = true;
                q.emplace(R, C, sword);
            }
        }
    }
    if (ans == -1) cout << "Fail";
    else cout << ans;
    return 0;
}