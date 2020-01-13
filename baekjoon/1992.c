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
void QuadTree(int** arr, int x, int y, int len)
{
    switch (COLOR(arr, x, y, len)) {
    case -1:
        printf("(");
        QuadTree(arr, x, y, len / 2);
        QuadTree(arr, x, y + len / 2, len / 2);
        QuadTree(arr, x + len / 2, y, len / 2);
        QuadTree(arr, x + len / 2, y + len / 2, len / 2);
        printf(")");
        break;
    case 0:
        printf("0");
        break;
    case 1:
        printf("1");
        break;
    }
}
int main()
{
    int len;
    char c;
    scanf("%d", &len);

    int** arr = malloc(sizeof(int*) * len);
    for (int i = 0; i < len; i++)
        arr[i] = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        getchar();
        for (int j = 0; j < len; j++) {
            scanf("%c", &c);
            arr[i][j] = (int)c - 48;
        }
    }

    QuadTree(arr, 0, 0, len);
    return 0;
}