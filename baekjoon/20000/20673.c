#include <stdio.h>

int main() {
    int p, q;
    scanf("%d%d", &p, &q);
    if (p <= 50 && q <= 10) {
        puts("White");
    } else if (q > 30) {
        puts("Red");
    } else {
        puts("Yellow");
    }
}
