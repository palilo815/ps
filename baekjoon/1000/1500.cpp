#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll s, k, a, b, c;
    cin >> s >> k;

    a = s / k;		// 몫
    b = s - a * k;	// 나머지
    c = k - b;
    ll ans = 1;
    while (c--) ans *= a;
    while (b--) ans *= (a + 1);
    cout << ans;
    return 0;
}