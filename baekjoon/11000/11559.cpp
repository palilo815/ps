#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int mov[4][2] = { -1,0,1,0,0,-1,0,1 };
char board[12][6];
bool visited[12][6];
void down(int c)
{
    // 빈칸 i 위에 블록칸 j가 있을경우 swap(i,j)를 해준다.
    loop(i, 12)
        if (board[i][c] == '.')
            for (int j = i + 1; j < 12; ++j) {
                if (board[j][c] != '.') {
                    swap(board[i][c], board[j][c]);
                    break;
                }
                // 위에 아무 블록이 없을 경우, 나머지 i를 고려할 필요가 없다. 바로 return
                if (j == 11) return;
            }
}
int DFS(int r, int c, char colour)
{
    int ret = 1;
    visited[r][c] = true;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R == -1 || R == 12 || C == -1 || C == 6) continue;
        if (board[R][C] == colour && !visited[R][C])
            ret += DFS(R, C, colour);
    }
    return ret;
}
void boom(int r, int c, int colour)
{
    board[r][c] = '.';
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R == -1 || R == 12 || C == -1 || C == 6) continue;
        if (board[R][C] == colour)
            boom(R, C, colour);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 항상 블록은 아래쪽으로 모이기 때문에
    // row를 역순으로 저장하는게 편하다.
    for (int i = 11; i >= 0; --i) loop(j, 6)
        cin >> board[i][j];
    int ans = 0;
    while (1) {
        bool no_boom = true;
        loop(i, 12) loop(j, 6)
            // 색깔 블록을 발견하면
            if (board[i][j] != '.') {
                // 연결된 블록의 개수를  count에 저장
                int count = DFS(i, j, board[i][j]);
                memset(visited, 0, sizeof(visited));

                // 만약 4개 이상이면 터뜨린다.
                if (count >= 4) {
                    boom(i, j, board[i][j]);
                    no_boom = false;
                }
            }

        // 만약 위에서 아무 폭발이 없었다면 끝.
        if (no_boom) break;
        // 폭발이 있었다면, 빈 칸 위의 블록을 아래로 내려준다.
        else loop(i, 6) down(i);
        ++ans;
    }
    cout << ans;
    return 0;
}