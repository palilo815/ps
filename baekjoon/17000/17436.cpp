#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)
typedef long long ll;

int main() {
    int N;
    ll M;
    scanf("%d %lld", &N, &M);

    int prime[10];
    loop(i, N) scanf("%d", &prime[i]);
    
    ll ans = M;
    loop(i, 1 << N) {
        int sign = (__builtin_popcount(i) & 1) ? 1 : -1;
        ll p = 1;
        loop(j, N) if (i & (1 << j))
            p *= prime[j];
        ans += M / p * sign;
    }
    printf("%lld", ans);
    return 0;
}