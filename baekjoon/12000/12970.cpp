#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

int main() {
    int N, K; scanf("%d%d", &N, &K);

    int A = N / 2, B = (N + 1) / 2;
    if (A * B < K) {
        puts("-1");
        return 0;
    }

    int A_front = K / B, B_front = B - K % B;

    loop(i, A_front) putchar('A');
    loop(i, B_front) putchar('B');
    if (B != B_front) putchar('A');
    loop(i, B - B_front) putchar('B');
    loop(i, A - A_front - (B != B_front)) putchar('A');
    return 0;
}