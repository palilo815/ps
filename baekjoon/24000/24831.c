#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    for (int x, y, a, b; t--;) {
        scanf("%d%d%d%d", &x, &y, &a, &b);
        y -= x, a += b;
        printf("%d\n", y % a ? -1 : y / a);
    }
}
