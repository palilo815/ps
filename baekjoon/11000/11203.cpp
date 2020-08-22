#include <cstdio>

int main() {
    int h; scanf("%d ", &h);
    h = 1 << (h + 1);

    int i = 1;
    for (char c; (c = getchar()) != EOF && c != '\n';) {
        i <<= 1;
        if (c == 'R') ++i;
    }
    printf("%d", h - i);
    return 0;
}