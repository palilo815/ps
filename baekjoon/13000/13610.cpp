#include <cstdio>

int main() {
    int x, y; scanf("%d %d", &x, &y);
    printf("%d", (y - 1) / (y - x) + 1);
    return 0;
}