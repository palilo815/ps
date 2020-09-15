#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int mxN = 1e3;

int a[mxN + 1], b[mxN + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T, A, B; cin >> T;
    cin >> A;
    LOOP(i, A) cin >> a[i];
    cin >> B;
    LOOP(i, B) cin >> b[i];

    partial_sum(a + 1, a + A + 1, a + 1);
    partial_sum(b + 1, b + B + 1, b + 1);

    vector<int> vt;
    LOOP(i, A) LOOP(j, i) vt.emplace_back(a[i] - a[j - 1]);

    sort(vt.begin(), vt.end());
    vt.emplace_back(INT_MAX);

    long long ans = 0;
    LOOP(i, B) LOOP(j, i) {
        int key = T - (b[i] - b[j - 1]);
        auto it = lower_bound(vt.begin(), vt.end(), key);
        if (*it == key) ans += upper_bound(vt.begin(), vt.end(), key) - it;
    }
    cout << ans;
    return 0;
}