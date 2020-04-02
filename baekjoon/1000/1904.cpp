#include <cstdio>

int main() {
    int N; scanf("%d", &N);
    int a = 1, b = 1;
    for (int i = 2; i <= N; ++i) {
        int c = (a + b) % 15746;
        a = b, b = c;
    }
    printf("%d", b);
    return 0;
}