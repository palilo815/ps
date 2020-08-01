#include <cstdio>

int main() {
    int x = 0, y = 0;
    for (int a, b, t = 3; t--; x ^= a, y ^= b)
        scanf("%d%d", &a, &b);
    printf("%d %d", x, y);
    return 0;
}