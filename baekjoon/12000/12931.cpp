#include <cstdio>
#define max(a,b) (a>b?a:b)

int main() {
    int N; scanf("%d", &N);
    int ans = 0, mul2 = 0;

    for (int x; N; --N) {
        scanf("%d", &x);
        ans += __builtin_popcount(x);
        mul2 = max(mul2, 31 - __builtin_clz(x));
    }
    printf("%d", ans + mul2);
    return 0;
}