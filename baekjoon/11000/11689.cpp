#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    // https://ko.wikipedia.org/wiki/오일러_피_함수
    ll n; cin >> n;
    ll tmp = n, ans = n;
    for (ll i = 2; i * i <= n; ++i)
        if (tmp % i == 0) {
            ans = ans / i * (i - 1);
            while (tmp % i == 0) tmp /= i;
        }
    if (tmp != 1) ans = ans / tmp * (tmp - 1);
    cout << ans;
    return 0;
}