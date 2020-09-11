#include <bits/stdc++.h>
using namespace std;

const int mxM = 1e5;

int a[mxM];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int M, N, L; cin >> M >> N >> L;
    for (int i = 0; i < M; ++i)
        cin >> a[i];

    sort(a, a + M);

    int ans = 0;
    for (int x, y; N--;) {
        cin >> x >> y;
        if (y > L) continue;

        auto it = lower_bound(a, a + M, x - (L - y));
        if (it != a + M && *it <= x + L - y)
            ++ans;
    }
    cout << ans;
    return 0;
}