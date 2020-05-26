#include <cstdio>
typedef long long ll;

const int p = 1000000007;

ll power(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = (res * x) % p;
        y /= 2;
        x = (x * x) % p;
    }
    return res;
}
ll inv(ll n) {
    return power(n, p - 2);
}
int main() {
    int n, r; scanf("%d %d", &n, &r);
    if (r == 0) { putchar('1'); return 0; }

    ll fac = 1, fac_r1 = 1, fac_r2 = 1;
    for (int i = 1; i <= n; ++i) {
        fac = fac * i % p;
        if (i == r) fac_r1 = fac;
        if (i == n - r) fac_r2 = fac;
    }

    printf("%lld", fac * inv(fac_r1) % p * inv(fac_r2) % p);
    return 0;
}