#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    for (int n; t--;) {
        scanf("%d", &n);
        puts(n & 1 ? "koosaga" : "cubelover");
    }
}
