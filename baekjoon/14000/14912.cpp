#include <iostream>
using namespace std;

int count_d(int n, int d)
{
    int ret = 0;
    while (n) {
        if (n % 10 == d) ++ret;
        n /= 10;
    }
    return ret;
}
int main()
{
    int n, d; cin >> n >> d;
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += count_d(i, d);
    cout << ans;
    return 0;
}