#include <stdio.h>

int main() {
    int b;
    scanf("%d", &b);
    const int p = 5 * b - 400;
    printf("%d\n%d", p, p == 100 ? 0 : (p < 100 ? 1 : -1));
}
