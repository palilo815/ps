#include <cstdio>

void swap(int& x, int& y) {
    int t = x; x = y; y = t;
}
int main() {
    int a, b, c; scanf("%d %d %d", &a, &b, &c);
    if (a > b) swap(a, b);
    if (b > c) swap(b, c);
    if (a > b) swap(a, b);

    if (a == b && b == c) putchar('2');
    else if (a * a + b * b == c * c) putchar('1');
    else putchar('0');
    return 0;
}