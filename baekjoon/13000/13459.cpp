#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int MAX = 10;

char board[MAX][MAX];
bool visited[MAX][MAX][MAX][MAX];

void lean(int a, int b, int d) {

}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    int ry = 0, rx = 0, by = 0, bx = 0;
    loop(i, row) loop(j, col) {
        cin >> board[i][j];
        if (board[i][j] == 'R') ry = i, rx = j;
        if (board[i][j] == 'B') by = i, bx = j;
    }

    visited[ry][rx][by][bx] = true;
    int cnt = 0;
    queue<int> q;
    q.push(ry * 1000 + rx * 100 + by * 10 + bx), q.push(-1);

    while (1) {
        ry = q.front(); q.pop();
        if (ry == -1) {
            if (++cnt > 10) { cnt = -1; break; }
            q.push(-1);
            continue;
        }
        bx = ry % 10; ry /= 10;
        by = ry % 10; ry /= 10;
        rx = ry % 10; ry /= 10;
        

    }
    return 0;
}