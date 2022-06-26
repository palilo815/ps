#include <stdio.h>

int main() {
    int a;
    scanf("%d", &a);
    printf("%.9lf\n%.9lf", 100.0 / a, 100.0 / (100 - a));
}
