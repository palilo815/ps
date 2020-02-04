#include <iostream>
using namespace std;
const int max_N = 1000;

int psum[max_N + 1][max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, Q;
    cin >> row >> col >> Q;
    for (int i = 1;i <= row;++i)
        for (int j = 1;j <= col;++j) {
            int x; cin >> x;
            psum[i][j] = x + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
        }
    while (Q--) {
        int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
        int ans = psum[y2][x2] - psum[y1 - 1][x2] - psum[y2][x1 - 1] + psum[y1 - 1][x1 - 1];
        cout << ans / ((y2 - y1 + 1) * (x2 - x1 + 1)) << '\n';
    }
    return 0;
}