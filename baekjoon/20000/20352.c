#include <math.h>
#include <stdio.h>

int main() {
    long long a;
    scanf("%lld", &a);
    printf("%.9lf", 2 * a / sqrt(a / 3.14159265358979323846));
}
