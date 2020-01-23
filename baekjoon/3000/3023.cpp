#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char card[100][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> card[i][j];
    loop(i, row) for (int j = col; j < 2 * col; ++j)
        card[i][j] = card[i][2 * col - j - 1];
    for (int i = row; i < 2 * row; ++i) loop(j, 2 * col)
        card[i][j] = card[2 * row - i - 1][j];

    int y, x; cin >> y >> x;
    if (card[y - 1][x - 1] == '.') card[y - 1][x - 1] = '#';
    else card[y - 1][x - 1] = '.';

    loop(i, 2 * row) {
        loop(j, 2 * col) cout << card[i][j];
        cout << '\n';
    }
    return 0;
}