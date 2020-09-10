#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        a[i] -= x;
    }

    int ans = 0;
    for (int i = 0, j; i < N;) {
        if (!a[i]) {++i; continue;}
        for (j = i + 1; j < N && a[i] * a[j] > 0; ++j) ;

        int mn = *min_element(a + i, a + j, [&](int& a, int& b) {
            return abs(a) < abs(b);
        });

        ans += abs(mn);
        for (int k = i; k < j; ++k)
            a[k] -= mn;
    }
    cout << ans;
    return 0;
}