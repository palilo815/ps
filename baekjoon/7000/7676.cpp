#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 1000;

int R, N, a[mx];

void solve() {
    loop(i, N) cin >> a[i];
    sort(a, a + N);

    int j, ans = 0;
    loop(i, N) {
        ++ans;
        for (j = i; j + 1 < N && a[j + 1] - a[i] <= R; ++j) ;
        i = j;
        while (j + 1 < N && a[j + 1] - a[i] <= R) ++j;
        i = j;
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    for (;;) {
        cin >> R >> N;
        if (R == -1) break;
        solve();
    }
    return 0;
}