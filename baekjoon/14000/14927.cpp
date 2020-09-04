#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int mxN = 20;

int ans = INT_MAX;
bool mat[mxN][mxN], tmp[mxN][mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    LOOP(i, N) LOOP(j, N) cin >> mat[i][j];

    function<void(int, int)> flip = [&](int r, int c) {
        tmp[r - 1][c] ^= 1;
        tmp[r][c - 1] ^= 1;
        tmp[r][c] ^= 1;
        tmp[r][c + 1] ^= 1;
        tmp[r + 1][c] ^= 1;
    };

    int ans = INT_MAX;
    for (int fst = 0; fst < 1 << N; ++fst) {
        int cnt = __builtin_popcount(fst);
        move(mat[1], mat[N + 1], tmp[1]);

        LOOP(c, N) if (fst & (1 << (c - 1)))
            flip(1, c);

        for (int r = 2; r <= N && cnt < ans; ++r)
            LOOP(c, N) if (tmp[r - 1][c]) {
                ++cnt;
                flip(r, c);
            }

        if (cnt < ans && none_of(tmp[N] + 1, tmp[N] + N + 1, [&](auto& x) {return x;}))
            ans = cnt;
    }
    cout << (ans == INT_MAX ? -1 : ans);
    return 0;
}