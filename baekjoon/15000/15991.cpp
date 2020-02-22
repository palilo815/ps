#include <stdio.h>
#define scanf scanf_s
const int mod = 1000000009;
const int max_N = 100000;

int DP[max_N + 6];

int main() {
    for (int i = 0; i < 4; ++i) DP[i] = 1;
    for (int i = 0; i < max_N; ++i) {
        DP[i + 2] += DP[i], DP[i + 2] %= mod;
        DP[i + 4] += DP[i], DP[i + 4] %= mod;
        DP[i + 6] += DP[i], DP[i + 6] %= mod;
    }
    int T; scanf("%d", &T);
    while (T--) {
        int q; scanf("%d", &q);
        printf("%d\n", DP[q]);
    }
    return 0;
}