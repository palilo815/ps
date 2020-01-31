#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int ans = 0, x;
    while (cin >> x)
        if (x > 0) ++ans;
    cout << ans;
    return 0;
}