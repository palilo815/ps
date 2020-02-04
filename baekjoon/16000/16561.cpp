#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    n /= 3;
    int ans = 0;
    for (int i = 1; i <= n - 2; ++i)
        for (int j = 1;i + j < n;++j)
            ++ans;
    cout << ans;
    return 0;
}