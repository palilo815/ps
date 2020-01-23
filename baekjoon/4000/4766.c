#include <stdio.h>

int main()
{
    double prev, curr;
    scanf("%lf", &prev);
    while (1) {
        scanf("%lf", &curr);
        if (curr == 999) break;
        printf("%.2lf\n", curr - prev);
        prev = curr;
    }
    return 0;
}