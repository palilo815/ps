#include <stdio.h>

int main() {
    int p;
    scanf("%d", &p);
    for (int k, n; p--;) {
        scanf("%d%d", &k, &n);
        printf("%d %d\n", k, n * (n + 3) / 2);
    }
}

