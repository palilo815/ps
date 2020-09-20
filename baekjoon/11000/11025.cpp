#include <cstdio>

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K, ans = 0;
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; ++i)
        ans = (ans + K) % i;
    printf("%d", ans + 1);
    return 0;
}