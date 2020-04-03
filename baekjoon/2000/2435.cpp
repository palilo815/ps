#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <climits>
#define loop(i,n) for(int i=0;i<n;++i)

int T[100];
int main() {
    int N, K; scanf("%d %d", &N, &K);
    loop(i, N) scanf("%d", &T[i]);

    int ans = INT_MIN;
    loop(i, N - K + 1) {
        int sum = 0;
        loop(j, K) sum += T[i + j];
        if (sum > ans) ans = sum;
    }
    printf("%d", ans);
    return 0;
}