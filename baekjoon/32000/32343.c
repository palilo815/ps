#include <stdio.h>

int main() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    int zeros = a + b < n ? (n - a - b) : (a + b - n);
    printf("%d", ((1 << n) - 1) ^ ((1 << zeros) - 1));
}
