#include <stdio.h>

int main()
{
    int ans[8] = { 1,2,3,4,5,4,3,2 };
    int n;
    scanf("%d", &n);
    printf("%d", ans[(n - 1) % 8]);
    return 0;
}