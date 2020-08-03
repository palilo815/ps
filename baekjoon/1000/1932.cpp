#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)
#define max(x,y) (x>y?x:y)

const int mx = 500;

int a[mx], dp[mx];

int main() {
    int N; scanf("%d", &N);
    loop(r, N) {
        loop(i, r + 1) scanf("%d", a + i);
        for (int i = r; i; --i)
            dp[i] = max(dp[i - 1], dp[i]) + a[i];
        dp[0] += a[0];
    }

    int ans = 0;
    loop(i, N) ans = max(ans, dp[i]);
    printf("%d", ans);
    return 0;
}