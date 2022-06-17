#include <stdio.h>

int main() {
    int n, c;
    scanf("%d%d", &n, &c);
    int a = n, b = n;
    for (int x, y; c--;) {
        scanf("%d%d", &x, &y);
        if (x >= a || y >= b) continue;
        (x * b < a * y) ? (b = y) : (a = x);
    }
    printf("%d", a * b);
}
