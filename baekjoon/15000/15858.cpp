#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

int main()
{
    ll a, b, c;
    cin >> a >> b >> c;

    ll D = a * b;
    ll E = D / c;
    D -= E * c;
    cout << E << '.';
    double F = 1.0 * D / c;
    loop(i, 10) {
        F *= 10;
        cout << int(F);
        while (F >= 1) --F;
    }
    return 0;
}