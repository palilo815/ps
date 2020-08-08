#include <bits/stdc++.h>
using namespace std;

const int mx = 100;

int a[mx], b[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    N = unique(a, a + N) - a;
    copy(a, a + N, b);
    sort(b, b + N);

    int ans = 0;
    for (int i = 0; i < N; ++i)
        ans += a[i] != b[i];

    if (ans) --ans;
    cout << ans;
    return 0;
}