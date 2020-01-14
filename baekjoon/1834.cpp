#include<iostream>
using namespace std;
#define ll long long

int main()
{
    ll n, ans = 0;
    cin >> n;
    for (ll i = 1;i < n;++i)
        // n으로 나누면 몫이 i이고 나머지도 i
        ans += n * i + i;
    cout << ans;
    return 0:
}