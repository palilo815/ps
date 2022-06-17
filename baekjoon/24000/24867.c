#include <stdio.h>

long long max(long long x, long long y) { return x > y ? x : y; }

int main() {
    long long k, a, x, b, y;
    scanf("%lld%lld%lld%lld%lld", &k, &a, &x, &b, &y);
    printf("%lld", max(max(0, k - a) * x + max(0, k - a - b) * y, max(0, k - b) * y + max(0, k - b - a) * x));
}
