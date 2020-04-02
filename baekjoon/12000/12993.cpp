#include <cstdio>
#define scanf scanf_s
int main() {
    int x, y; scanf("%d %d", &x, &y);
    while (x || y) {
        if (x % 3 + y % 3 != 1) {
            putchar('0');
            return 0;
        }
        x /= 3, y /= 3;
    }
    putchar('1');
    return 0;
}