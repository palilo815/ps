#include <cstdio>

int main() {
    int x, k; scanf("%d %d", &x, &k);
    x *= 1000, k *= 7000;

    for (int i = 0; i < 3; ++i, k /= 2)
        if (k <= x) {
            printf("%d", k);
            return 0;
        }
    putchar('0');
    return 0;
}