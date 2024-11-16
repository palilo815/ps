#include <stdio.h>

int main() {
    int n;
    long long m;
    scanf("%d%lld", &n, &m);
    int primes[10];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &primes[i]);
    }
    long long ans = m;
    for (int i = 0; i < 1 << n; ++i) {
        long long prod = 1;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {
                prod *= primes[j];
            }
        }
        long long sign = __builtin_parity(i) ? 1 : -1;
        ans += m / prod * sign;
    }
    printf("%lld", ans);
}
