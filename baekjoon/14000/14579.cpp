#include <iostream>
using namespace std;
const int MOD = 14579;

int main()
{
    // sum[1,a] * sum[1,a+1] *  ~~    * sum[1,b]
    int a, b, ans = 1;
    cin >> a >> b;
    for (int i = a; i <= b; ++i) {
        ans *= (1 + i) * i / 2;
        ans %= MOD;
    }
    cout << ans;
    return 0;
}