#include <stdio.h>

int main()
{
    int t;
    scanf("%d", &t);
    double cost;
    while (t--) {
        scanf("%lf", &cost);
        printf("$%.2lf\n", cost * 0.8);
    }
    return 0;
}