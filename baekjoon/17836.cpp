#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

struct hero {
    int y;
    int x;
    int sword;
};

int castle[100][100];
bool visited[2][100][100];
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
queue<hero> q;
void Insert(int y, int x, int sword) {
    hero tmp;
    tmp.y = y;
    tmp.x = x;
    tmp.sword = sword;
    q.push(tmp);
}
int main()
{
    int row, col, T;
    cin >> row >> col >> T;
    loop(i, row) loop(j, col)
        cin >> castle[i][j];

    Insert(0, 0, 0);
    Insert(-1, -1, 0);
    int ans = 0;

    while (ans <= T) {
        hero curr = q.front(); q.pop();
        if (curr.y == -1) {
            ++ans; q.push(curr);
            continue;
        }
        if (curr.y == row - 1 && curr.x == col - 1) break;
        if (castle[curr.y][curr.x] == 2)
            curr.sword = true;
        loop(i, 4) {
            int Y = curr.y + mov[i][0], X = curr.x + mov[i][1];
            if (Y < 0 || Y == row || X < 0 || X == col || visited[curr.sword][Y][X]) continue;
            if (!visited[curr.sword][Y][X] && (castle[Y][X] != 1 || (castle[Y][X] == 1 && curr.sword))) {
                visited[curr.sword][Y][X] = true;
                Insert(Y, X, curr.sword);
            }
        }
    }
    if (ans > T) cout << "Fail";
    else cout << ans;
    return 0;
}