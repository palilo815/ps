#include<iostream>
using namespace std;
int main()
{
    int n, ans = 1, len = 6;
    cin >> n;
    if (n == 1) {
        cout << '1';
        return 0;
    }
    n--;
    while (n > len) {
        ans++;
        n -= len;
        len += 6;
    }
    cout << ans + 1 << '\n';
    return 0;
}