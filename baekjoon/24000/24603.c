#include <stdio.h>

int main() {
    int n, x, y;
    scanf("%d%d%d", &n, &x, &y);
    for (int a; n--; ) {
        scanf("%d", &a);
        printf("%d\n", a * y / x);
    }
}
