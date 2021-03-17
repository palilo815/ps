#include <bits/stdc++.h>
using namespace std;

constexpr int mxB = 250;
constexpr int add[12][12] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
    1, 2, 0, 4, 5, 3, 7, 8, 6, 10, 11, 9,
    2, 0, 1, 5, 3, 4, 8, 6, 7, 11, 9, 10,
    3, 4, 5, 0, 1, 2, 9, 10, 11, 6, 7, 8,
    4, 5, 3, 1, 2, 0, 10, 11, 9, 7, 8, 6,
    5, 3, 4, 2, 0, 1, 11, 9, 10, 8, 6, 7,
    6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5,
    7, 8, 6, 10, 11, 9, 1, 2, 0, 4, 5, 3,
    8, 6, 7, 11, 9, 10, 2, 0, 1, 5, 3, 4,
    9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2,
    10, 11, 9, 7, 8, 6, 4, 5, 3, 1, 2, 0,
    11, 9, 10, 8, 6, 7, 5, 3, 4, 2, 0, 1};

int grundy[mxB][mxB];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (int i = 0; i < mxB; ++i)
        grundy[0][i] = grundy[i][0] = i;

    bitset<384> mask;
    for (int x = 1; x < mxB; ++x)
        for (int y = 1; y < mxB; ++y) {
            mask.reset();
            for (int X = x - 1; ~X; --X)
                mask[grundy[X][y]] = true;
            for (int Y = y - 1; ~Y; --Y)
                mask[grundy[x][Y]] = true;

            for (int i = 0;; ++i)
                if (!mask[i]) {
                    grundy[x][y] = i;
                    break;
                }
        }

    int n;
    cin >> n;

    int sum = 0;
    for (int x, y; n--;) {
        cin >> x >> y;
        sum ^= 12 * grundy[x / 12][y / 12] + add[x % 12][y % 12];
    }

    cout << (sum ? "koosaga" : "cubelover");
}