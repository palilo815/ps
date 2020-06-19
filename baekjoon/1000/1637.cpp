#include <bits/stdc++.h>
#define loop(i,n) for(ui i=0;i<n;++i)
using namespace std;
using ui = unsigned;

const ui M = 20000;

ui N, A[M], B[M], C[M];

ui solve(ui m) {
    ui ret = 0;
    loop(i, N) if (m >= A[i])
        ret += (min(C[i], m) - A[i]) / B[i] + 1;
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> A[i] >> C[i] >> B[i];

    ui l = 0, r = INT_MIN;
    while (l < r) {
        ui m = (l + r) >> 1;
        solve(m) & 1 ? (r = m) : (l = m + 1);
    }

    if (l <= INT_MAX) cout << l << ' ' << solve(l) - solve(l - 1);
    else cout << "NOTHING";
    return 0;
}