#include <stdio.h>

int bad(char* s) {
    if ('B' <= *s && *s <= 'F') ++s;
    if (*s != 'A') return 0;
    while (*s == 'A') ++s;
    if (*s != 'F') return 0;
    while (*s == 'F') ++s;
    if (*s != 'C') return 0;
    while (*s == 'C') ++s;
    if ('A' <= *s && *s <= 'F') ++s;
    return *s == 0;
}

int main() {
    int t;
    scanf("%d", &t);
    for (char s[201]; t--;) {
        scanf("%s", s);
        puts(bad(s) ? "Infected!" : "Good");
    }
}
