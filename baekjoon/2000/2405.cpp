#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);

    int ans = 0;
    for (int i = 0; i < N - 2; ++i)
        ans = max(ans, abs(a[i] - a[i + 1] * 2 + a[N - 1]));
    for (int i = 1; i < N - 1; ++i)
        ans = max(ans, abs(a[0] - a[i] * 2 + a[i + 1]));
    cout << ans;
    return 0;
}