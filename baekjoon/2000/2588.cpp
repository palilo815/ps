#include <cstdio>

int main() {
    int a, b; scanf("%d%d", &a, &b);
    printf("%d\n%d\n%d\n%d", a * (b % 10), a * (b % 100 / 10), a * (b / 100), a * b);
    return 0;
}