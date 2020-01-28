#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int n, U = 0, a[100];
    double d;
    while (1) {
        scanf("%lf", &d);
        if (d == 0) break;
        scanf("%d", &n);
        loop(i, n) scanf("%d", &a[i]);
        printf("User %d\n", ++U);
        loop(i, n) printf("%.5lf\n", d * a[i] / 100000);
    }
    return 0;
}