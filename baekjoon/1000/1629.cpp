#include <cstdio>
typedef unsigned long long ull;

int main() {
    ull A, B, C;
    scanf("%llu %llu %llu", &A, &B, &C);

    ull ans = 1;
    while (B) {
        if (B & 1) ans = ans * A % C;
        A = A * A % C;
        B >>= 1;
    }
    printf("%llu", ans);
}