#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;

void mov_down(char board[][8])
{
    loop(c, 8)
        if (board[7][c] == '#')
            board[7][c] = '.';
    loop(c, 8)
        for (int r = 6; r >= 0; --r)
            if (board[r][c] == '#') {
                board[r][c] = '.';
                board[r + 1][c] = '#';
            }
}
int main()
{
    // 시작, 도착점과 board 크기는 고정이다.
    char board[8][8];
    loop(i, 8) loop(j, 8) cin >> board[i][j];
    queue<P> q;
    q.push({ 7, 0 }), q.push({ -1, -1 });

    while (1) {
        int r = q.front().first, c = q.front().second; q.pop();
        // 도착
        if (r == 0 && c == 7) break;
        // pivot
        if (r == -1) {
            if (q.empty()) break;
            mov_down(board);
            q.push({ -1, -1 });
            continue;
        }
        // 벽이 움직여서 플레이어를 덮쳤다면 사망
        if (board[r][c] == '#') continue;
        // 제자리에 가만히 있을 수 있다.
        q.push({ r, c });
        // 이동
        // i==0 && j==0은 제자리에 있는 경우므로 무시한다.
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int R = r + i, C = c + j;
                if (R == -1 || R == 8 || C == -1 || C == 8) continue;
                if (board[R][C] == '.') {
                    board[R][C] = 'o';
                    q.push({ R, C });
                }
            }
    }
    cout << !q.empty();
    return 0;
}