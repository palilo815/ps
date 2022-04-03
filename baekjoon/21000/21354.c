#include <stdio.h>

int main() {
    int a, p;
    scanf("%d%d", &a, &p);
    a *= 7, p *= 13;
    if (a > p) {
        puts("Axel");
    } else if (a < p) {
        puts("Petra");
    } else {
        puts("lika");
    }
}
