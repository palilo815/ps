#include <cstdio>

const int mx = 1000;

char a[mx], b[mx];

int main() {
    int N; scanf("%d", &N);
    scanf("\n%s%s", a, b);

    int ans = 0;
    for (int i = 0, diff = 0; i < N; ++i) {
        if (a[i] == b[i]) {ans += diff != 0; diff = 0;}
        else ++diff;
    }
    printf("%d", ans);
    return 0;
}