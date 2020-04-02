#include <cstdio>
typedef long long ll;

const int mapping[10] = { 0,1,2,-1,-1,5,9,-1,8,6 };

bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}
int main() {
    ll num, inv = 0;
    scanf("%lld", &num);
    if (!is_prime(num)) goto FAIL;
    while (num) {
        int x = mapping[num % 10];
        if (x == -1) goto FAIL;
        inv = 10 * inv + x;
        num /= 10;
    }
    if (!is_prime(inv)) goto FAIL;
    printf("yes");
    return 0;
FAIL:;
    printf("no");
    return 0;
}