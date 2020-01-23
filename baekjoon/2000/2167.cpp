#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int psum[301][301];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    for (int i = 1; i <= row; ++i) for (int j = 1; j <= col; ++j) {
        int x; cin >> x;
        psum[i][j] = x + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
    }

    int n; cin >> n;
    while (n--) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        cout << psum[r2][c2] - psum[r1 - 1][c2] - psum[r2][c1 - 1] + psum[r1 - 1][c1 - 1] << '\n';
    }
    return 0;
}