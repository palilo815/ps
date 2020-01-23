#include<bits/stdc++.h>
using namespace std;
int Count2(int n)
{
    int ret = 0;
    while (n)
        n /= 2, ret += n;
    return ret;
}
int Count5(int n)
{
    int ret = 0;
    while (n)
        n /= 5, ret += n;
    return ret;
}
int main()
{
    int n, r;
    cin >> n >> r;
    int five = Count5(n) - Count5(r) - Count5(n - r);
    int two = Count2(n) - Count2(r) - Count2(n - r);
    cout << min(five, two);
    return 0;
}