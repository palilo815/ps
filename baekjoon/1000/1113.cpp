#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int row, col, ans;
int pool[50][50];
bool visited[50][50];
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

bool posi(int r, int c) {
    visited[r][c] = true;
    bool ret = true;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R == row || C < 0 || C == col) return false;
        if (visited[R][C]) continue;
        if (pool[R][C] < pool[r][c]) return false;
        else if (pool[R][C] == pool[r][c]) ret = ret && posi(R, C);
    }
    return ret;
}
void Add(int r, int c, int prev) {
    ++pool[r][c], ++ans;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R == row || C < 0 || C == col) continue;
        if (pool[R][C] == prev)
            Add(R, C, prev);
    }
}
int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        pool[i][j] = c - '0';
    }
    loop(i, row) loop(j, col) {
        while (posi(i, j)) {
            Add(i, j, pool[i][j]);
            memset(visited, 0, sizeof(visited));
        }
        memset(visited, 0, sizeof(visited));
    }
    cout << ans;
    return 0;
}