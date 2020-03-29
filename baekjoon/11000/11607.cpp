#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int MAX = 500;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

char board[MAX][MAX];
bool visited[MAX][MAX];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> board[i][j];

    queue<p> q;
    q.emplace(0, 0), q.emplace(-1, -1);
    visited[0][0] = true;

    int ans = 0;
    while (1) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans; q.emplace(-1, -1);
            continue;
        }
        if (r == row - 1 && c == col - 1) break;

        int jump = board[r][c] - '0';
        if (!jump) continue;
        loop(i, 4) {
            int R = r + mov[i][0] * jump, C = c + mov[i][1] * jump;
            if (R < 0 || R >= row || C < 0 || C >= col || visited[R][C]) continue;
            visited[R][C] = true;
            q.emplace(R, C);
        }
    }
    if (ans == -1) cout << "IMPOSSIBLE";
    else cout << ans;
    return 0;
}