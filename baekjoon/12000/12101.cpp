#include <bits/stdc++.h>
using namespace std;

const int max_N = 10;
int DP[max_N + 1];
vector<int> ans;

void solve(int n, int k) {
    if (n == 0) return;
    for (int i = 1; i <= 3; ++i) {
        if (DP[n - i] >= k) {
            ans.emplace_back(i);
            solve(n - i, k);
            return;
        }
        k -= DP[n - i];
    }
}
int main() {
    int N, K; cin >> N >> K;
    DP[0] = 1, DP[1] = 1, DP[2] = 2;
    for (int i = 3; i <= N; ++i)
        DP[i] = DP[i - 1] + DP[i - 2] + DP[i - 3];

    if (K > DP[N]) { cout << -1; return 0; }

    solve(N, K);
    for (int i = 0; i < ans.size(); ++i) {
        if (i) cout << '+';
        cout << ans[i];
    }
    return 0;
}