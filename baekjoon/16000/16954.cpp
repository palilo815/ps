#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

char board[8][8];
void mov_down() {
    loop(c, 8) if (board[7][c] == '#')
        board[7][c] = '.';
    loop(c, 8) for (int r = 6; r >= 0; --r)
        if (board[r][c] == '#') {
            board[r][c] = '.';
            board[r + 1][c] = '#';
        }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    loop(i, 8) loop(j, 8) cin >> board[i][j];
    queue<p> q;
    q.emplace(7, 0), q.emplace(-1, -1);

    while (1) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {
            if (q.empty()) break;
            mov_down();
            q.emplace(-1, -1);
            continue;
        }
        if (r == 0 && c == 7) break;
        if (board[r][c] == '#') continue;
        
        q.emplace(r, c);
        for (int i = -1; i <= 1; ++i) for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int R = r + i, C = c + j;
            if (R == -1 || R == 8 || C == -1 || C == 8) continue;
            if (board[R][C] == '.') {
                board[R][C] = 'o';
                q.emplace(R, C);
            }
        }
    }
    cout << !q.empty();
    return 0;
}