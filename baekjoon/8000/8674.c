#include <stdio.h>

int main() {
    unsigned x, y;
    scanf("%u%u", &x, &y);
    printf("%u", (x & 1 && y & 1) ? (x < y ? x : y) : 0);
}
