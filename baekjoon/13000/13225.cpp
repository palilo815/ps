#include <iostream>
using namespace std;

int main()
{
    int t, n, d;
    cin >> t;
    while (t--) {
        cin >> n;
        d = 0;
        for (int i = 2; i <= n / 2; ++i)
            if (n % i == 0) ++d;
        if (n == 1) --d;
        cout << n << ' ' << d + 2 << '\n';
    }
    return 0;
}