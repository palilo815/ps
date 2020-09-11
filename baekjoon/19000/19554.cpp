#include <cstdio>

int main() {
    int l = 1, r;
    scanf("%d", &r);

    while (l ^ r) {
        int m = (l + r) >> 1;
        printf("? %d\n", m);
        fflush(stdout);

        int res; scanf("%d", &res);
        if (res == -1) l = m + 1;
        else if (res == 1) r = m - 1;
        else l = r = m;
    }
    printf("= %d\n", l);
    return 0;
}