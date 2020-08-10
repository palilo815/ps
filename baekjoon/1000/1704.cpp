#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int mx = 17;

bool ori[mx][mx], mat[mx][mx], tmp[mx][mx], ans[mx][mx];
int cnt;

void flip(int r, int c) {
    ++cnt;
    tmp[r][c] = true;
    mat[r][c] = !mat[r][c];
    mat[r][c - 1] = !mat[r][c - 1];
    mat[r][c + 1] = !mat[r][c + 1];
    mat[r + 1][c] = !mat[r + 1][c];
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int R, C; cin >> R >> C;
    LOOP(i, R) LOOP(j, C) cin >> ori[i][j];

    int mn = INT_MAX;
    for (int fst = 0; fst < 1 << C; ++fst) {
        cnt = 0;
        memset(tmp, 0, sizeof(tmp));
        copy(ori[1], ori[R + 1], mat[1]);

        LOOP(i, C) if (fst & (1 << (C - i)))
            flip(1, i);

        LOOP(i, R - 1) LOOP(j, C) if (mat[i][j])
            flip(i + 1, j);

        if (cnt < mn && (none_of(mat[R] + 1, mat[R] + C + 1, [&](auto x) {return x;}))) {
            mn = cnt;
            copy(tmp[1], tmp[R + 1], ans[1]);
        }
    }
    if (mn == INT_MAX) cout << "IMPOSSIBLE";
    else {
        LOOP(i, R) {
            LOOP(j, C) cout << ans[i][j] << ' ';
            cout << '\n';
        }
    }
    return 0;
}