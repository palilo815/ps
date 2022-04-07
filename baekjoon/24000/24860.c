#include <stdio.h>

int main() {
    int v, j;
    scanf("%d%d", &v, &j);
    long long res0 = v * j;
    scanf("%d%d", &v, &j);
    long long res1 = v * j;
    int d;
    scanf("%d%d%d", &v, &d, &j);
    res0 *= v * d * j;
    res1 *= v * d * j;
    printf("%lld", res0 + res1);
}
