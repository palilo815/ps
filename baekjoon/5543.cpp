#include<iostream>
using namespace std;

int main()
{
    int b1, b2, b3, d1, d2;
    cin >> b1 >> b2 >> b3 >> d1 >> d2;
    int ans = b1;
    if (b2 < ans) ans = b2;
    if (b3 < ans) ans = b3;
    ans += (d1 < d2) ? d1 : d2;
    cout << ans - 50;
    return 0;
}