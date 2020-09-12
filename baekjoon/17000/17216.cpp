#include <bits/stdc++.h>
using namespace std;

const int mxX = 1001;

int dp[mxX + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int x; N--;) {
        cin >> x;
        dp[x] = max(dp[x], x + *max_element(dp + x + 1, dp + mxX));
    }
    cout << *max_element(dp + 1, dp + mxX);
    return 0;
}