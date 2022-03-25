#include <stdio.h>

int main() {
    int n, k, m = 0;
    scanf("%d%d", &n, &k);
    if (n > 60 + k) {
        m = n - 60 - k;
        n = 60 + k;
    }
    printf("%d", 1500 * n + 3000 * m);
}
