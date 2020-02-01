#include <iostream>
using namespace std;

int main()
{
    int n, i, ans = 0;
    cin >> n;
    for (i = 1; i * i < n; ++i)
        if (n % i == 0) ans += 2;
    if (i * i == n) ++ans;
    cout << ans;
    return 0;
}