#include <bits/stdc++.h>
using namespace std;

const int mx = 3188646;

int K, dp[mx + 1];

int SK(int n) {
    int ret = 0;
    for (; n; n /= 10)
        ret += pow(n % 10, K);
    return ret;
}
void solve(int n) {
    vector<int> stk;
    int x = n;

    for (; !dp[x]; x = SK(x)) {
        stk.emplace_back(x);
        dp[x] = -1;
    }

    x = ~dp[x] ? dp[x] : *min_element(find(stk.begin(), stk.end(), x), stk.end());
    for (; !stk.empty(); stk.pop_back()) {
        x = min(stk.back(), x);
        dp[stk.back()] = x;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int A, B;
    cin >> A >> B >> K;

    long long ans = 0;
    for (int i = A; i <= B; ++i) {
        if (!dp[i]) solve(i);
        ans += dp[i];
    }
    cout << ans;
}