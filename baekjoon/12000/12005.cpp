#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

int a[mxN + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);
    a[N] = INT_MAX;

    int ans = 0;
    for (int i = 0, j = 0; j < N; ++i) {
        while (a[j] - a[i] <= K) ++j;
        ans = max(ans, j - i);
    }
    cout << ans;
    return 0;
}