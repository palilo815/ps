#include <cstdio>
#define max(x,y) (x>y?x:y)

int main() {
    int N; scanf("%d", &N);
    int a = 100, b = 100, c;
    int d = 0, t = 100;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &c);
        if (max(a, c) < t) d = i - 1, t = max(a, c);
        a = b; b = c;
    }
    printf("%d %d", d, t);
    return 0;
}