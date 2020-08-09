#include <bits/stdc++.h>
using namespace std;

const int mx = 5e5;

int a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    sort(a, a + N);

    int cnt = N, ans = 0;
    for (int i = 0; i < N && cnt; ++i) {
        if (a[i] < cnt - 1) ans += a[i], cnt -= a[i] + 1;
        else ans += cnt - 1, cnt = 0;
    }
    cout << ans;
    return 0;
}