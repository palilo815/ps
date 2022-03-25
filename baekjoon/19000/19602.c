#include <stdio.h>

int main() {
    int s, m, l;
    scanf("%d%d%d", &s, &m, &l);
    puts(s + 2 * m + 3 * l < 10 ? "sad" : "happy");
}
