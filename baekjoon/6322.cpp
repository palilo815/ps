#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c;
    int T = 0;
    while (1) {
        scanf("%lf %lf %lf", &a, &b, &c);
        if (a == 0 && b == 0 && c == 0) break;
        printf("Triangle #%d\n", ++T);
        if (c == -1) {
            c = sqrt(a * a + b * b);
            printf("c = %.3lf\n\n", c);
        }
        else {
            if (a + b + 1 >= c) printf("Impossible.\n\n");
            else {
                if (a == -1) putchar('a');
                else putchar('b');
                a = a + b + 1;
                a = sqrt(c * c - a * a);
                printf(" = %.3lf\n\n", a);
            }
        }
    }
    return 0;
}