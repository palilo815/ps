#include <stdio.h>

int main() {
    for (int i = 2, t, f, s, p, c; i--; ) {
        scanf("%d%d%d%d%d", &t, &f, &s, &p, &c);
        printf("%d ", 6 * t + 3 * f + 2 * s + p + 2 * c);
    }
}
