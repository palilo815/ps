#include <cstdio>

const int max_N = 21;

long long DP[max_N];

int main() {
    DP[2] = 1;
    for (int i = 3; i < max_N; ++i)
        DP[i] = (i - 1) * (DP[i - 2] + DP[i - 1]);

    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        printf("%lld\n", DP[n]);
    }
    return 0;
}