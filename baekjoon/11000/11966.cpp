#include <stdio.h>

int main()
{
    int n; scanf("%d", &n);
    printf("%d", (n == 1 || (n & (n - 1)) == 0));
    return 0;
}