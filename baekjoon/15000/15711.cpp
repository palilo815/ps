#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxsq = 2e6;

bitset<mxsq> sieve;
vector<int> prime;

bool is_prime(ll n) {
    if (!(n & 1)) return n != 0;
    if (n == 1) return false;
    for (int& x : prime) {
        if ((ll)x * x > n) break;
        if (n % x == 0) return false;
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i < mxsq; ++i)
        if (!sieve[i])
            for (int j = i * i; j < mxsq; j += i)
                sieve[j] = true;

    for (int i = 2; i < mxsq; ++i)
        if (!sieve[i])
            prime.emplace_back(i);

    int T;
    cin >> T;
    for (ll a, b; T--;) {
        cin >> a >> b;
        cout << (is_prime(a + b - 2) ? "YES\n" : "NO\n");
    }
    return 0;
}