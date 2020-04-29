#include <cstdio>

const int max_N = 1000000;

int DP[max_N + 1];

int sum(int n) {
    int ret = 0;
    while (n) {
        ret += n % 10;
        n /= 10;
    }
    return ret;
}
int main() {
    int N; scanf("%d", &N);
    for (int u = 1; u <= N; ++u) {
        ++DP[u];
        int v = u + sum(u);
        if (v <= N) DP[v] += DP[u];
    }
    printf("%d", DP[N]);
    return 0;
}