#include <stdio.h>

int main()
{
    int N, X, a;
    scanf("%d %d", &N, &X);
    while (N--) {
        scanf("%d", &a);
        if (a < X) printf("%d ", a);
    }
    return 0;
}