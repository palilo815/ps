#include <stdio.h>

int main() {
    int w1, h1, w2, h2;
    scanf("%d%d%d%d", &w1, &h1, &w2, &h2);
    printf("%d", 4 + 2 * (h1 + h2 + (w1 > w2 ? w1 : w2)));
}
