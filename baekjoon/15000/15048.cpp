#include <cstdio>

char n[101];

int main() {
    scanf("%s", n);
    int x = 0;
    for (int i = 0; n[i]; ++i)
        x = (10 * x + n[i] - '0') % 3;
    printf("%d", x);
    return 0;
}