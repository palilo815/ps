#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    int ans = 0, x = 5;
    while (n >= x) {
        ans += n / x;
        x *= 5;
    }
    cout << ans;
    return 0;
}