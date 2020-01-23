#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char img[1000][1000], key, num;
int row, col, mov[4][2] = { -1,0,1,0,0,-1,0,1 };
void DFS(int r, int c)
{
    img[r][c] = num;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || img[R][C] != key)
            continue;
        DFS(R, C);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> img[i][j];
    int r, c; cin >> r >> c >> num;
    key = img[r][c];
    if (key != num)
        DFS(r, c);
    loop(i, row) {
        loop(j, col) cout << img[i][j];
        cout << '\n';
    }
    return 0;
}