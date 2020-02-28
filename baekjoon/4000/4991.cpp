#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int MAX = 20;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int board[MAX][MAX];
bool visited[MAX][MAX][1 << 10];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    while (1) {
        int row, col; cin >> col >> row;
        if (row == 0) break;

        memset(board, 0, sizeof(board));
        memset(visited, 0, sizeof(visited));

        queue<tup> q;
        int cnt = 0; char x;
        loop(i, row) loop(j, col) {
            cin >> x;
            if (x == 'x') board[i][j] = -1;
            else if (x == '*') board[i][j] = ++cnt;
            else if (x == 'o') { q.push({ i,j,0 }); visited[i][j][0] = true; }
        }
        q.push({ -1,-1,-1 });

        int ans = 0;
        while (1) {
            auto [r, c, mask] = q.front(); q.pop();

            if (r == -1) {
                if (q.empty()) { ans = -1; break; }
                q.push({ -1,-1,-1 }); ++ans;
                continue;
            }
            if (mask == (1 << cnt) - 1) break;

            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (R < 0 || R >= row || C < 0 || C >= col || board[R][C] == -1) continue;
                int MASK = (board[R][C] ? mask | (1 << (board[R][C] - 1)) : mask);
                if (!visited[R][C][MASK]) {
                    visited[R][C][MASK] = true;
                    q.push({ R,C,MASK });
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}