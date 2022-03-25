#include <stdio.h>

int main() {
    int a, x, b, y, t;
    scanf("%d%d%d%d%d", &a, &x, &b, &y, &t);
    printf("%d %d", a + 21 * x * (t > 30 ? t - 30 : 0), b + 21 * y * (t > 45 ? t - 45 : 0));
}
