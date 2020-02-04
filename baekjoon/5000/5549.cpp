#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000;

int psum[max_N + 1][max_N + 1][3];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, Q;
    cin >> row >> col >> Q;

    char x;
    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j) {
            loop(k, 3) psum[i][j][k] = psum[i - 1][j][k] + psum[i][j - 1][k] - psum[i - 1][j - 1][k];
            cin >> x;
            if (x == 'J') ++psum[i][j][0];
            else if (x == 'O') ++psum[i][j][1];
            else ++psum[i][j][2];
        }

    int y1, x1, y2, x2;
    while (Q--) {
        cin >> y1 >> x1 >> y2 >> x2;
        loop(k, 3) cout << psum[y2][x2][k] - psum[y2][x1 - 1][k] - psum[y1 - 1][x2][k] + psum[y1 - 1][x1 - 1][k] << ' ';
        cout << '\n';
    }
    return 0;
}