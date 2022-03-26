#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    const int m = (a + b + c) / 3;
    printf("%d", c - m + (b + c - m - m));
}
