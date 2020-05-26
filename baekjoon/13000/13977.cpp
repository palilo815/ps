#include <iostream>
using namespace std;
typedef long long ll;

const int max_N = 4000000;
const int p = 1000000007;

int fac[max_N + 1];

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
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    fac[0] = 1;
    for (int i = 1; i <= max_N; ++i)
        fac[i] = (ll)fac[i - 1] * i % p;

    int T; cin >> T;
start:;
    int n, r; cin >> n >> r;
    if (r) cout << fac[n] * inv(fac[r]) % p * inv(fac[n - r]) % p;
    else cout << 1;
    cout << '\n';

    if (--T) goto start;
    return 0;
}