#include <stdio.h>

int main() {
    int t1, v1, t2, v2;
    scanf("%d%d%d%d", &t1, &v1, &t2, &v2);
    if (t2 < 0 && v2 >= 10) {
        puts("A storm warning for tomorrow! Be careful and stay home if possible!");
    } else if (t1 > t2) {
        puts("MCHS warns! Low temperature is expected tomorrow.");
    } else if (v1 < v2) {
        puts("MCHS warns! Strong wind is expected tomorrow.");
    } else {
        puts("No message");
    }
}
