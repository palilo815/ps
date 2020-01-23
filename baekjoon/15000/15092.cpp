#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int row, col, mov[8][2] = { -1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1 };
char M[100][100];
void DFS(int r, int c)
{
    M[r][c] = '.';
    loop(i, 8) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || M[R][C] == '.') continue;
        DFS(R, C);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int ans = 0;
    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> M[i][j];
    loop(i, row) loop(j, col)
        if (M[i][j] == '#') {
            DFS(i, j);
            ++ans;
        }
    cout << ans;
    return 0;
}