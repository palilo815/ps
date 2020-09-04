#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 5e4;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, D, L;
    cin >> N >> M >> D >> L;
    loop(i, N) cin >> a[i];

    sort(a, a + N);

    int ans = 0;
    loop(i, N) if (a[i] - ans / M * D >= L)
        ++ans;
    cout << ans;
    return 0;
}