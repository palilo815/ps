#include <cstdio>

int main() {
    char a, b, c;
    scanf("%c %c %c", &a, &b, &c);
    putchar(a == b ? a : c);
    return 0;
}