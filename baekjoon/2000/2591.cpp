#include <cstdio>

int main() {
    char s[41];
    scanf("%s", s);

    int a = 1, b = s[0] != '0';
    int c = b;
    for (int i = 1; s[i]; ++i) {
        c = 0;
        if (s[i] != '0') c += b;
        if (s[i - 1] == '1' || s[i - 1] == '2' || s[i - 1] == '3' && s[i] < '5') c += a;
        a = b; b = c;
    }
    printf("%d", c);
    return 0;
}