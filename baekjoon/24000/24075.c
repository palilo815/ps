#include <stdio.h>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n%d", a + (b < 0 ? -b : b), a + (b < 0 ? b : -b));
}
