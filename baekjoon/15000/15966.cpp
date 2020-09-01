#include <bits/stdc++.h>
using namespace std;

const int mxA = 1e6 + 1;

int dp[mxA];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int x; N; --N) {
        cin >> x;
        dp[x] = dp[x - 1] ? dp[x - 1] + 1 : 1;
    }
    cout << *max_element(dp, dp + mxA);
    return 0;
}