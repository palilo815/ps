#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000000;
const int max_N = 100;

int N;
int DP[max_N + 1][10][1 << 10];

int solve(int len, int last, int used) {
    if (len == N) return (used == (1 << 10) - 1);

    int& ret = DP[len][last][used];
    if (ret != -1) return ret;

    ret = 0;
    if (last - 1 >= 0) ret += solve(len + 1, last - 1, used | (1 << (last - 1)));
    if (last + 1 < 10) ret += solve(len + 1, last + 1, used | (1 << (last + 1)));
    return ret = ret % mod;
}
int main() {
    memset(DP, -1, sizeof(DP));
    cin >> N;
    int ans = 0;
    for (int i = 1; i < 10; ++i)
        ans = (ans + solve(1, i, 1 << i)) % mod;
    cout << ans;
    return 0;
}