#include <stdio.h>

int main()
{
    double M;
    while (1) {
        scanf("%lf", &M);
        if (M == 0) break;
        double R = M * 5280 / 4854;
        printf("%.2lf English miles equals %.2lf Roman miles or %.0lf paces.\n", M, R, R * 1000);
    }
    return 0;
}