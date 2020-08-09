#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 1e3;

int maxh[mx << 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    long long ans = 0;
    int R, C; cin >> R >> C;
    loop(i, R) loop(j, C) {
        int h; cin >> h;
        ans += h;
        maxh[i] = max(maxh[i], h);
        maxh[R + j] = max(maxh[R + j], h);
    }

    sort(maxh, maxh + R + C);
    cout << ans - accumulate(maxh, unique(maxh, maxh + R + C), 0ll);
    return 0;
}