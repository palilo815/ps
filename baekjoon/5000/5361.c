#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    double cost[5] = { 350.34, 230.90, 190.55, 125.30, 180.90 };
    int t, cnt;
    scanf("%d", &t);
    while (t--) {
        double sum = 0;
        loop(i, 5) {
            scanf("%d", &cnt);
            sum += cost[i] * cnt;
        }
        printf("$%.2lf\n", sum);
    }
    return 0;
}