#include <stdio.h>

int main() {
    int wc, hc, ws, hs;
    scanf("%d%d%d%d", &wc, &hc, &ws, &hs);
    printf("%d", wc > ws + 1 && hc > hs + 1);
}
