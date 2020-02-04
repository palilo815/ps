#include <stdio.h>
#define PI 3.14159265358979323846

int main()
{
    double a, r, p1, p2;
    scanf("%lf %lf %lf %lf", &a, &p1, &r, &p2);
    double slice = a / p1, whole = PI * r * r / p2;
    if (slice > whole) printf("Slice of ");
    else printf("Whole ");
    printf("pizza");
    return 0;
}