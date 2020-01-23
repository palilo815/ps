#include <stdio.h>
#define PI 3.141592

int main()
{
    double d, r;
    scanf("%lf %lf", &d, &r);
    printf("%.8lf", 2.0 * (d + PI * r));
    return 0;
}