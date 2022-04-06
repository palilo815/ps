#include <stdio.h>
#include <math.h>

const double PI = 3.14159265358979323846;

int main() {
    long long a;
    scanf("%lld", &a);
    printf("%lf", 2 * PI * sqrt(a / PI));
}
