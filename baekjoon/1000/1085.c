#include <stdio.h>
#include <stdlib.h>
int main()
{
    int x, y, A, B;
    scanf("%d %d %d %d", &x, &y, &A, &B);
    int way[4] = { x, y, };
    way[2] = A - x;
    way[3] = B - y;
    int min = way[0];
    for (int i = 1; i < 4; i++) {
        if (way[i] < min)
            min = way[i];
    }
    printf("%d", min);
    return 0;
}