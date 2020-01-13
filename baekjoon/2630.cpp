#include <stdio.h>
#include <stdlib.h>
int COLOR(int** arr, int x, int y, int len)
{
    int color = arr[x][y];
    for (int i = x; i < x + len; i++) {
        for (int j = y; j < y + len; j++) {
            if (color != arr[i][j])
                return -1;
        }
    }
    return color;
}
void NUM_ColoredPaper(int** arr, int x, int y, int len, int* sum_white, int* sum_blue)
{
    switch (COLOR(arr, x, y, len)) {
    case -1:
        NUM_ColoredPaper(arr, x, y, len / 2, sum_white, sum_blue);
        NUM_ColoredPaper(arr, x, y + len / 2, len / 2, sum_white, sum_blue);
        NUM_ColoredPaper(arr, x + len / 2, y, len / 2, sum_white, sum_blue);
        NUM_ColoredPaper(arr, x + len / 2, y + len / 2, len / 2, sum_white, sum_blue);
        break;
    case 0:
        (*sum_white)++;
        break;
    case 1:
        (*sum_blue)++;
        break;
    }
}
int main()
{
    int sum_white = 0, sum_blue = 0;
    int len;
    scanf("%d", &len);

    int** arr = malloc(sizeof(int*) * len);
    for (int i = 0; i < len; i++)
        arr[i] = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            scanf("%d", &arr[i][j]);

    NUM_ColoredPaper(arr, 0, 0, len, &sum_white, &sum_blue);

    printf("%d\n%d", sum_white, sum_blue);
    return 0;
}