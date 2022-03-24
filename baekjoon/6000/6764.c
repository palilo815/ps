#include <stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    if (a < b && b < c && c < d) {
        puts("Fish Rising");
    } else if (a > b && b > c && c > d) {
        puts("Fish Diving");
    } else if (a == b && b == c && c == d) {
        puts("Fish At Constant Depth");
    } else {
        puts("No Fish");
    }
}
