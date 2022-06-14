#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int a, b, c; n--;) {
        scanf("%d%d%d", &a, &b, &c);
        const int ans = (a + b == c) || (a - b == c) || !(a % b) && (a / b == c) ||
                        (a * b == c) || (b - a == c) || !(b % a) && (b / a == c);
        puts(ans ? "Possible" : "Impossible");
    }
}
