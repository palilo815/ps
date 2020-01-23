#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll a, b, sum_a, sum_b;
    cin >> a >> b;

    if (a < 0) sum_a = -(a * (a - 1) / 2);
    else sum_a = a * (a + 1) / 2;
    if (b < 0) sum_b = -(b * (b - 1) / 2);
    else sum_b = b * (b + 1) / 2;
    
    ll ans;
    if (a >= 0 && b >= 0) ans = abs(sum_a - sum_b) + min(a, b);
    else if (a < 0 && b < 0) ans = -abs(sum_a - sum_b) + max(a, b);
    else ans = sum_a + sum_b;
    cout << ans;
    return 0;
}