#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char parking[50][50];
int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int ans[5] = {};
    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> parking[i][j];
    loop(car, 5) loop(r, row - 1) loop(c, col - 1) {
        int cnt = 0;
        loop(i, 2) loop(j, 2) {
            if (parking[r + i][c + j] == '#') goto OUT;
            if (parking[r + i][c + j] == 'X') ++cnt;
        }
        if (cnt == car) ++ans[car];
    OUT:;
    }
    loop(i, 5) cout << ans[i] << '\n';
    return 0;
}