#include <stdio.h>

const int max_N = 100000;
int psum[max_N + 1];
int main()
{
    int N, x; scanf("%d", &N);
    for (int i = 1;i <= N;++i) {
        scanf("%d", &x);
        psum[i] = psum[i - 1] + x;
    }
    scanf("%d", &N);
    int a, b;
    while(N--) {
        scanf("%d %d", &a, &b);
        printf("%d\n", psum[b] - psum[a - 1]);
    }
    return 0;
}