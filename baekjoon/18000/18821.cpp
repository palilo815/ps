#include <cstdio>

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int N; scanf("%d", &N);
        printf("%c\n", (N == 1 ? 'E' : 'O'));
    }
    return 0;
}