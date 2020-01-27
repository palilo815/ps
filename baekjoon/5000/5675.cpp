#include <stdio.h>

int main()
{
    int A;
    while (scanf("%d", &A) != -1) {
        if (A % 6) printf("N\n");
        else printf("Y\n");
    }
    return 0;
}