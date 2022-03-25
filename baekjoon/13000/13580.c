#include <stdio.h>

int main() {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    char ans = 'N';
    if (x == y || y == z || z == x) {
        ans = 'S';
    }
    int mx = x > y ? x : y;
    if (z > mx) {
        mx = z;
    }
    if (x + y + z - mx == mx) {
        ans = 'S';
    }
    putchar(ans);
}
