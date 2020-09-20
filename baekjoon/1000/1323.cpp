#include <cstdio>
using ll = long long;

const int mxK = 1e5;

bool check[mxK];

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    ll N, d = 1;
    int K;
    scanf("%lld%d", &N, &K);

    for (int tmp = N; tmp; tmp /= 10, d *= 10)
        ;

    ll x = N % K;
    int ans = 1;
    while (x) {
        if (check[x]) {
            ans = -1;
            break;
        }
        check[x] = true;
        x = (x * d + N) % K;
        ++ans;
    }
    printf("%d", ans);
    return 0;
}