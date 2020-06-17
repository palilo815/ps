#include <cstdio>

int main() {
    int a, b, c; scanf("%d %d %d", &a, &b, &c);
    int m = a < b ? a : b;
    m = m < c ? m : c;
    printf("%d", a + b + c - m);
    return 0;
}