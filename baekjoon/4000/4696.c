#include <stdio.h>

int main() {
    for (double x;;) {
        scanf("%lf", &x);
        if (!x) break;
        printf("%.2lf\n", 1 + x + x * x + x * x * x + x * x * x * x);
    }
}
