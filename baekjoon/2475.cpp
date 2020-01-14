#include<iostream>
using namespace std;

int main()
{
    int t = 5, ans = 0, n;
    while (t--) {
        cin >> n;
        ans += n * n;
    }
    cout << ans % 10;
    return 0;
}