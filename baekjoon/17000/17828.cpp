#include <stdio.h>

int main() {
    int N, X; scanf("%d %d", &N, &X);
    if (X < N || 26 * N < X) {
        putchar('!'); return 0;
    }

    for (int i = N; i > 0; --i) {
        if (X - 1 <= 26 * (i - 1)) putchar('A');
        else {
            int tmp = 26 * (i - 1) - X;
            putchar('A' - tmp - 1);
            for (; i > 1; --i) putchar('Z');
        }
        --X;
    }
    return 0;
}