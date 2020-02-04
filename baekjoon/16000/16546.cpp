#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll sum, n, x;
    cin >> n;
    sum = (1 + n) * n / 2;
    while (--n) {
        cin >> x;
        sum -= x;
    }
    cout << sum;
    return 0;
}