#include <bits/stdc++.h>
using namespace std;
struct food {
    int p, s;
};

const int mxN = 10;
const int mxA = 200;

food a[mxN];
bool dp[mxA + 1];

int solve() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].p >> a[i].s;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.p + a.s < b.p + b.s;
    });
    memset(dp + 1, 0, mxA);

    for (int i = 0; i < N; ++i)
        for (int j = a[i].p; ~j; --j)
            if (dp[j])
                dp[j + a[i].s] = true;

    for (int i = mxA; ~i; --i)
        if (dp[i])
            return i;
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    dp[0] = true;

    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        cout << "Case #" << t << ": " << solve() << '\n';
    return 0;
}