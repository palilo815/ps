#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll n, sum = 0, x;
    cin >> n;
    n *= n;
    while (n--) {
        cin >> x;
        sum += x;
    }
    cout << sum;
    return 0;
}