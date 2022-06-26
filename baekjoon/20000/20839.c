#include <assert.h>
#include <stdio.h>

int main() {
    int a, c, e, x, y, z;
    scanf("%d%d%d%d%d%d", &a, &c, &e, &x, &y, &z);
    char ans = '?';
    if (z == e) {
        ans = 'E';
        if (y == c) {
            ans = 'C';
            if (x == a) {
                ans = 'A';
            } else if (x * 2 >= a) {
                ans = 'B';
            }
        } else if (y * 2 >= c) {
            ans = 'D';
        }
    }
    assert(ans != '?');
    putchar(ans);
}
