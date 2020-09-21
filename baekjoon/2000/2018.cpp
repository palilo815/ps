#include <cstdio>

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    scanf("%d", &N);

    int ans = 0;
    for (int k = 1; N > k * (k - 1) / 2; ++k)
        // a1 + a2 + ... + ak = N
        // a1 + (a1 + 1) + (a1 + 2) + ... + (a1 + k - 1) = N
        // ka1 + k(k - 1) / 2 = N
        // ka1 = N - k(k - 1) / 2
        if ((N - k * (k - 1) / 2) % k == 0) ++ans;
    printf("%d", ans);
    return 0;
}