#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long

int main()
{
    ull n; cin >> n;
    ull ans = sqrtl(n);
    if (pow(ans, 2) < n)
        ++ans;
    cout << ans;
    return 0;
}