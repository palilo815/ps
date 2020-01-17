#include <bits/stdc++.h>
#define loop(i,n) for(int i=0; i<n; ++i)
#define P pair<int,int>
using namespace std;

P operator+(const P& a, const P& b) {
    return { a.first + b.first,a.second + b.second };
}
char M[250][250];
int row, col, mov[4][2] = { -1,0,0,-1,0,1,1,0 };

P DFS(int r, int c)
{
    P ret = { 0,0 };
    if (M[r][c] == 'k') ++ret.first;
    else if (M[r][c] == 'v') ++ret.second;
    M[r][c] = '#';
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || M[R][C] == '#') continue;
        ret = ret + DFS(R, C);
    }
    return ret;
}
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int sheep = 0, wolf = 0;
    cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> M[i][j];
    loop(i, row) loop(j, col)
        if (M[i][j] != '#') {
            P cnt = DFS(i, j);
            if (cnt.first > cnt.second)
                sheep += cnt.first;
            else
                wolf += cnt.second;
        }
    cout << sheep << ' ' << wolf;
    return 0;
}