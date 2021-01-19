#include <bits/stdc++.h>
using namespace std;

const int mxR = 3e3;

int mat[mxR + 1][mxR + 1], psum[mxR + 1][mxR + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int R, C, H, W;
    cin >> R >> C >> H >> W;

    for (int i = 1; i <= R; ++i)
        for (int j = 1; j <= C; ++j)
            cin >> mat[i][j];

    int key = (H * W) >> 1;
    auto valid = [&](int m) {
        for (int i = 1; i <= R; ++i)
            for (int j = 1; j <= C; ++j)
                psum[i][j] = (mat[i][j] <= m) + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
        for (int i = 0; i <= R - H; ++i)
            for (int j = 0; j <= C - W; ++j)
                if (psum[i + H][j + W] - psum[i + H][j] - psum[i][j + W] + psum[i][j] > key)
                    return true;
        return false;
    };

    int lo = 1, hi = R * C;
    while (lo != hi) {
        int m = (lo + hi) >> 1;
        valid(m) ? hi = m : lo = m + 1;
    }
    cout << lo;
}