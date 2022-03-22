#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    while (n & 1) n = (n + 1) >> 1;
    printf("%d", n);
}
