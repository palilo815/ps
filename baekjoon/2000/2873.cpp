#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

int main() {
    int R, C; scanf("%d %d", &R, &C);
    char r = 'R', l = 'L', u = 'U', d = 'D';
    if (R & 1 || C & 1) {
        if (C & 1) {
            r = 'D', d = 'R', l = 'U';
            int tmp = R; R = C; C = tmp;
        }
        loop(i, R / 2) {
            loop(j, C - 1) putchar(r); putchar(d);
            loop(j, C - 1) putchar(l); putchar(d);
        }
        loop(i, C - 1) putchar(r);
        return 0;
    }
    int m = 1000, min_r, min_c;
    loop(i, R) loop(j, C) {
        int x; scanf("%d", &x);
        if ((i + j) & 1 && x < m)
            m = x, min_r = i, min_c = j;
    }

    int i = 0, j = 0;
    while (i + 1 < min_r) {
        loop(k, C - 1) putchar(r); putchar(d);
        loop(k, C - 1) putchar(l); putchar(d);
        i += 2;
    }

    while (j + 1 < min_c) {
        printf("%c%c%c%c", d, r, u, r);
        j += 2;
    }

    if (min_r == i + 1) printf("%c%c", r, d);
    else printf("%c%c", d, r);
    i += 2, j += 2;

    while (j < C) {
        printf("%c%c%c%c", r, u, r, d);
        j += 2;
    }
    while (i < R) {
        putchar(d); loop(k, C - 1) putchar(l);
        putchar(d); loop(k, C - 1) putchar(r);
        i += 2;
    }
    return 0;
}