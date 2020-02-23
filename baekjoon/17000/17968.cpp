#include <stdio.h>
#include <string.h>
#define scanf scanf_s
const int max_N = 1000;

int a[max_N + 1];
bool check[max_N / 2 + 1];

int main() {
    int N; scanf("%d", &N);
    a[0] = a[1] = 1;
    for (int i = 2; i <= N; ++i) {
        memset(check, 0, sizeof(check));
        for (int k = 1; i - 2 * k >= 0; ++k) {
            int x = a[i - k] * 2 - a[i - 2 * k];
            if (x <= 500 && x >= 0) check[x] = true;
        }
        for (int j = 1; j <= 500; ++j)
            if (!check[j]) {
                a[i] = j;
                break;
            }
    }
    printf("%d", a[N]);
    return 0;
}