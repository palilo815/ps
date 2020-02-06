#include <iostream>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

int main()
{
    // A^X 알고리즘

    ll A, X; cin >> A >> X;
    A %= MOD;

    ll ans = 1;
    while (X) {
        if (X % 2) ans = (ans * A) % MOD;
        X /= 2;
        A = (A * A) % MOD;
    }
    cout << ans;
    return 0;
}