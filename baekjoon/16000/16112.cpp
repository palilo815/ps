#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mx = 3e5;

int a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);
    ll ans = 0;
    for (int i = 0; i < N; ++i)
        ans += (ll)a[i] * (i < K ? i : K);
    cout << ans;
    return 0;
}