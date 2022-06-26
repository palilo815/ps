#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if (a == b) {
        putchar(b == c ? '*' : 'C');
    } else {
        putchar(b == c ? 'A' : 'B');
    }
}
