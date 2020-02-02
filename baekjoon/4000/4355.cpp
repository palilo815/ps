#include <iostream>
using namespace std;

int main()
{
    // ** Euler phi function **

    while (1) {
        int n; cin >> n;
        if (n == 0) break;

        int tmp = n, ans = n;
        for (int i = 2; i * i <= n; ++i)
            if (tmp % i == 0) {
                ans = ans / i * (i - 1);
                while (tmp % i == 0) tmp /= i;
            }
        if (tmp > 1) ans = ans / tmp * (tmp - 1);
        cout << ans << '\n';
    }
    return 0;
}