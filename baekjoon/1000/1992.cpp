#include <stdio.h>

const int max_N = 64;

int quadT[max_N][max_N];

int colour(int r, int c, int len)
{
    int x = quadT[r][c];
    for (int i = r; i < r + len; ++i)
        for (int j = c; j < c + len; ++j)
            if (x != quadT[i][j])
                return -1;
    return x;
}
void zip(int r, int c, int len)
{
    int clr = colour(r, c, len);
    if (clr != -1) {
        printf("%d", clr);
        return;
    }
    len /= 2;
    putchar('(');
    zip(r, c, len);
    zip(r, c + len, len);
    zip(r + len, c, len);
    zip(r + len, c + len, len);
    putchar(')');
}
int main()
{
    int N; scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            scanf("%1d", &quadT[i][j]);
    zip(0, 0, N);
    return 0;
}