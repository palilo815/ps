#include <stdio.h>
#include<stdlib.h>
int COLOR(int** arr, int x, int y, int len)
{
    int color = arr[x][y];
    for (int i = x; i < x + len; i++) {
        for (int j = y; j < y + len; j++) {
            if (color != arr[i][j])
                return 2;
        }
    }
    return color;
}
void SUM(int** arr, int x, int y, int len, int* sum_neg, int* sum_zero, int* sum_pos)
{
    switch (COLOR(arr, x, y, len)) {
    case -1:
        (*sum_neg)++;
        break;
    case 0:
        (*sum_zero)++;
        break;
    case 1:
        (*sum_pos)++;
        break;
    case 2:
        SUM(arr, x, y, len / 3, sum_neg, sum_zero, sum_pos);
        SUM(arr, x, y + len / 3, len / 3, sum_neg, sum_zero, sum_pos);
        SUM(arr, x, y + 2 * len / 3, len / 3, sum_neg, sum_zero, sum_pos);
        SUM(arr, x + len / 3, y, len / 3, sum_neg, sum_zero, sum_pos);
        SUM(arr, x + len / 3, y + len / 3, len / 3, sum_neg, sum_zero, sum_pos);
        SUM(arr, x + len / 3, y + 2 * len / 3, len / 3, sum_neg, sum_zero, sum_pos);
        SUM(arr, x + 2 * len / 3, y, len / 3, sum_neg, sum_zero, sum_pos);
        SUM(arr, x + 2 * len / 3, y + len / 3, len / 3, sum_neg, sum_zero, sum_pos);
        SUM(arr, x + 2 * len / 3, y + 2 * len / 3, len / 3, sum_neg, sum_zero, sum_pos);
        break;
    }
}
int main()
{
    int len;
    int sum_neg = 0, sum_zero = 0, sum_pos = 0;
    scanf("%d", &len);

    int** arr = malloc(sizeof(int*) * len);
    for (int i = 0; i < len; i++)
        arr[i] = malloc(sizeof(int) * len);

    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            scanf("%d", &arr[i][j]);

    SUM(arr, 0, 0, len, &sum_neg, &sum_zero, &sum_pos);
    printf("%d\n%d\n%d", sum_neg, sum_zero, sum_pos);
    return 0;
}