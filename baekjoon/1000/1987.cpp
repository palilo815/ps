#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
char board[20][20];
bool visited[20][20], selected[26];
int row, col;

int DFS(int y, int x, int cnt)
{
    int ret = cnt;
    loop(i, 4) {
        int Y = y + mov[i][0], X = x + mov[i][1];
        if (Y < 0 || Y >= row || X < 0 || X >= col) continue;

        int alph = board[Y][X] - 'A';
        // 방문도 안했고, 해당 알파벳고 안골랐으면 DFS 전진
        if (!visited[Y][X] && !selected[alph]) {
            selected[alph] = visited[Y][X] = true;
            ret = max(ret, DFS(Y, X, cnt + 1));
            selected[alph] = visited[Y][X] = false;
        }
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> board[i][j];

    // 시작점은 먼저 체크
    selected[board[0][0] - 'A'] = true;
    visited[0][0] = true;

    cout << DFS(0, 0, 1);
    return 0;
}