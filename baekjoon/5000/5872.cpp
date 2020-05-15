#include <cstdio>

const int M = 100001;

char s[M];

int main() {
    scanf("%s", s);
    int stack = 0, ans = 0;
    for (int i = 0; s[i]; ++i) {
        if (s[i] == '(') ++stack;
        else {
            if (stack) --stack;
            else ++stack, ++ans;
        }
    }
    printf("%d", ans + stack / 2);
    return 0;
}