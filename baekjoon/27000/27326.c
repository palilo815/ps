#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int xorsum = 0;
    for (int x, i = 2 * n; --i;) {
        scanf("%d", &x);
        xorsum ^= x;
    }
    printf("%d", xorsum);
}
