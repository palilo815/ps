#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, c, d, e;
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
    int r = 0;
    r += abs(a - b) <= 1000;
    r += abs(a - c) <= 1000;
    r += abs(a - d) <= 1000;
    r += abs(a - e) <= 1000;
    printf("%d", r);
}
