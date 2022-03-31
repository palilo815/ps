#include <stdio.h>

int main() {
    int k;
    scanf("%d", &k);
    k += 2500;
    if (k < 10000) {
        k = 10000;
    } else if (k > 200000) {
        k = 200000;
    }
    printf("%d.%02d", k / 100, k % 100);
}
