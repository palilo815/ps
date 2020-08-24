#include <cstdio>

const int mx = 10;

char a[mx][mx + 1], b[mx << 1 | 1];

int main() {
    int R, C; scanf("%d%d\n", &R, &C);
    for (int i = 0; i < R; ++i)
        scanf("%s", a[i]);

    for (int i = 0; i < R; ++i) {
        scanf("%s", b);
        for (int j = 0; j < C; ++j)
            if (a[i][j] ^ b[j << 1] || a[i][j] ^ b[j << 1 | 1]) {
                puts("Not Eyfa");
                return 0;
            }
    }
    puts("Eyfa");
    return 0;
}