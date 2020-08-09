#include <bits/stdc++.h>
using namespace std;

const int mx = 1e5;

int a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    sort(a, a + N);

    long long ans = 0;
    for (int hp = 1, i = 0; i < N; ++i)
        if (a[i] >= hp) ans += a[i] - hp++;
    cout << ans;
    return 0;
}