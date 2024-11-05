#include <stdio.h>
#include <stdlib.h>

int n, vec[10];
char mat[10][10];

void f(int sz) {
    if (sz == n) {
        for (int i = 0; i < n; ++i) {
            printf("%d ", vec[i]);
        }
        exit(0);
    }
    for (int x = -10; x <= 10; ++x) {
        vec[sz] = x;
        int acc = 0;
        int ok = 1;
        for (int i = sz; ~i; --i) {
            acc += vec[i];
            ok &= mat[i][sz] == (acc ? (acc < 0 ? '-' : '+') : '0');
        }
        if (ok) {
            f(sz + 1);
        }
    }
}

int main() {
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            mat[i][j] = (char)getchar();
        }
    }
    f(0);
}
