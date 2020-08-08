#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, a[15]; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    sort(a, a + N, greater<int>());

    int ans[2] {};
    for (int i = 0; i < N; ++i)
        ans[i & 1] += a[i];
    cout << ans[0] << ' ' << ans[1];
    return 0;
}