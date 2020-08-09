#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 1e5;

int x[mx], y[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> x[i] >> y[i];

    sort(x, x + N);
    sort(y, y + N);

    long long ans = 0;
    int px = x[N / 2], py = y[N / 2];
    loop(i, N) ans += abs(x[i] - px) + abs(y[i] - py);
    cout << ans;
    return 0;
}