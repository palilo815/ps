#include <stdio.h>

int main()
{
    double d, a, b, f;
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %lf %lf %lf %lf", &n, &d, &a, &b, &f);
        printf("%d %.8lf\n", n, d / (a + b) * f);
    }
    return 0;
}