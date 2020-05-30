#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int M = 201;

int psum[M][M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int R, C; cin >> R >> C;
    LOOP(i, R) LOOP(j, C) {
        int x; cin >> x;
        psum[i][j] = x - psum[i - 1][j - 1] + psum[i - 1][j] + psum[i][j - 1];
    }

    int ans = INT_MIN;
    LOOP(sr, R) LOOP(sc, C)
        for (int er = sr; er <= R; ++er)
            for (int ec = sc; ec <= C; ++ec)
                ans = max(ans, psum[sr - 1][sc - 1] - psum[sr - 1][ec] - psum[er][sc - 1] + psum[er][ec]);
    cout << ans;
    return 0;
}