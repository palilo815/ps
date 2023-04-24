#include <stdio.h>

int main() {
    long long x;
    scanf("%lld", &x);
    if (x == 0) return putchar('0'), 0;
    long long y = 1;
    int ans = 1;
    while (y < x) {
        y <<= 1, ++ans;
    }
    printf("%d", ans);
}
