#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

int row, col;
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
char Map[50][50];
bool visited[50][50];

int BFS(int r, int c)
{
    memset(visited, 0, sizeof(visited));
    visited[r][c] = true;
    queue<P> q;
    q.push({ r,c }), q.push({ -1,-1 });
    int ret = 0;
    while (1) {
        int y = q.front().first, x = q.front().second; q.pop();
        if (y == -1) {
            if (q.empty()) break;
            ++ret; q.push({ y, x });
            continue;
        }
        loop(i, 4) {
            int Y = y + mov[i][0], X = x + mov[i][1];
            if (Y < 0 || Y == row || X < 0 || X == col || visited[Y][X] || Map[Y][X] == 'W') continue;
            visited[Y][X] = true;
            q.push({ Y, X });
        }
    }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> Map[i][j];

    int ans = 0;
    loop(i, row) loop(j, col) {
        if (Map[i][j] == 'L') {
            int tmp = BFS(i, j);
            if (tmp > ans) ans = tmp;
        }
    }
    cout << ans;
    return 0;
}