#include <cstdio>
#define LOOP(i,n) for(int i=1;i<=n;++i)

const int max_N = 1000001;

double DP[max_N];

int main() {
    int N; scanf("%d", &N);
    LOOP(i, N) {
        DP[i] += 1;
        LOOP(eye, 6) if (i - eye > 0)
            DP[i] += DP[i - eye] / 6;
    }
    printf("%.9lf", DP[N]);
    return 0;
}