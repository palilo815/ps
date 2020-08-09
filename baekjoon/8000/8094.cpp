#include <bits/stdc++.h>
using namespace std;

const int mx = 3e4;

int a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int M, N; cin >> M >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    sort(a, a + N);

    int ans = 0;
    for (int i = 0, j = N - 1; i <= j; --j, ++ans)
        if (a[i] + a[j] <= M) ++i;
    cout << ans;
    return 0;
}