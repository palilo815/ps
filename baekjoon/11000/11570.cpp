#include <bits/stdc++.h>
using namespace std;

const int max_N = 2001;

int dp[max_N][max_N];
int song[max_N];

int gap(int i, int j) { return j ? abs(song[i] - song[j]) : 0; }
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> song[i];

    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = 0;

    for (int i = 2; i <= N; ++i) {
        for (int j = 0, val1 = gap(i, i - 1); j < i - 1; ++j) {
            int val2 = gap(i, j);
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + val1);
            dp[i][i - 1] = min(dp[i][i - 1], dp[i - 1][j] + val2);
        }
    }
    cout << *min_element(dp[N], dp[N + 1]);
    return 0;
}