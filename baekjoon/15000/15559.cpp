#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int white = 0;
const int grey = -1;
const int black = 1;

char mat[1000][1000];
int colour[1000][1000];

int DFS(int r, int c) {
    if (colour[r][c] == black) return 0;
    if (colour[r][c] == grey) return 1;
    colour[r][c] = grey;
    int ret = 0;
    switch (mat[r][c]) {
    case 'N': ret = DFS(r - 1, c); break;
    case 'S': ret = DFS(r + 1, c); break;
    case 'W': ret = DFS(r, c - 1); break;
    case 'E': ret = DFS(r, c + 1);
    }
    colour[r][c] = black;
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> mat[i][j];
    int ans = 0;
    loop(i, row) loop(j, col)
        if (colour[i][j] == white)
            ans += DFS(i, j);
    cout << ans;
    return 0;
}