#include <stdio.h>

int main() {
    int d = 0;
    for (int t = 10, i; t--;) {
        scanf("%d", &i);
        d += i;
    }
    putchar("NESW"[d % 4]);
}
