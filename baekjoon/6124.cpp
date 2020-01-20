#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int Grass[100][100];
int sum(int r, int c)
{
    int ret = 0;
    loop(i, 3) loop(j, 3)
        ret += Grass[r + i][c + j];
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> Grass[i][j];

    int MAX = 0, y, x;
    loop(i, row - 2) loop(j, col - 2) {
        int tmp = sum(i, j);
        if (tmp > MAX) {
            MAX = tmp;
            y = i, x = j;
        }
    }
    cout << MAX << '\n' << y + 1 << ' ' << x + 1;
    return 0;
}