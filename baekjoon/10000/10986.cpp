#include <stdio.h>
typedef long long ll;

const int max_M = 1000;

int mod[max_M];

int main()
{
    int N, M; scanf("%d %d", &N, &M);
    int psum = 0;
    mod[0] = 1;
    for (int i = 1; i <= N; ++i) {
        int x; scanf("%d", &x);
        psum += x;
        psum %= M;
        ++mod[psum];
    }
    // mod[x] = psum % M == x인 개수
    // sum[a,b]는 psum[b] - psum[a-1]로 구할 수 있고
    // 이게 M으로 나누어 떨어지려면 psum[b]%M == psum[a-1]%M이어야 한다.
    // 즉 나머지가 같은 쌍이어야 하며,
    // mod[x] = cnt라면, 나머지가 x로 같은 쌍 cnt개가 있으므로,
    // cnt * (cnt - 1) / 2개의 쌍을 만들 수 있다.
    ll ans = 0;
    for (int i = 0; i < M; ++i) {
        ll cnt = mod[i];
        ans += cnt * (cnt - 1) / 2;
    }
    printf("%lld", ans);
    return 0;
}