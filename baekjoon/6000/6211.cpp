#include <bits/stdc++.h>
using namespace std;

const int mxC = 35001;

bitset<mxC> dp;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int C, N; cin >> C >> N;
    dp[0] = 1;
    for (int x; N; --N) {
        cin >> x;
        dp |= dp << x;
    }
    for (int i = C; ~i; --i)
        if (dp[i]) {
            cout << i;
            break;
        }
    return 0;
}