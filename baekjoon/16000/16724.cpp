#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 1000;
const int white = 0;
const int grey = -1;
const int black = 1;

char board[MAX][MAX];
short visited[MAX][MAX];

int DFS(int r, int c) {
    if (visited[r][c] == black) return 0;
    else if (visited[r][c] == grey) return 1;
    visited[r][c] = grey;
    int ret;
    switch (board[r][c]) {
    case 'U': ret = DFS(r - 1, c); break;
    case 'D': ret = DFS(r + 1, c); break;
    case 'L': ret = DFS(r, c - 1); break;
    case 'R': ret = DFS(r, c + 1); break;
    }
    visited[r][c] = black;
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> board[i][j];

    int ans = 0;
    loop(i, row) loop(j, col) if (!visited[i][j])
        ans += DFS(i, j);
    cout << ans;
    return 0;
}