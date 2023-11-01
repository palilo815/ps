#include <assert.h>
#include <stdio.h>

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0, g, d; i < k; ++i) {
        scanf("%d", &g);
        const int p = g * 100 / n;
        if (p <= 4) {
            d = 1;
        } else if (p <= 11) {
            d = 2;
        } else if (p <= 23) {
            d = 3;
        } else if (p <= 40) {
            d = 4;
        } else if (p <= 60) {
            d = 5;
        } else if (p <= 77) {
            d = 6;
        } else if (p <= 89) {
            d = 7;
        } else if (p <= 96) {
            d = 8;
        } else if (p <= 100) {
            d = 9;
        } else {
            assert(0);
        }
        printf("%d ", d);
    }
}
