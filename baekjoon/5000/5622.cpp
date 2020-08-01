#include <cstdio>

int main() {
    char s[16]; scanf("%s", s);
    int x = 0;
    for (int i = 0; s[i]; ++i)
        if (s[i] < 'S') x += (s[i] - 'A') / 3 + 3;
        else if (s[i] == 'S') x += 8;
        else if (s[i] < 'W') x += 9;
        else x += 10;
    printf("%d", x);
    return 0;
}