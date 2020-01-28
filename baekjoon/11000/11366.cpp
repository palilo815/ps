#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;

void multiply(ll F[][2], ll M[][2])
{
    ll x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    ll y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    ll z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    ll w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
    F[0][0] = x, F[0][1] = y, F[1][0] = z, F[1][1] = w;
}
void power(ll F[2][2], int n)
{
    if (n == 0 || n == 1) return;
    ll M[2][2] = { {1,1},{1,0} };
    power(F, n / 2);
    multiply(F, F);
    if (n % 2 == 1) multiply(F, M);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll a, b, n;
    while (1) {
        cin >> a >> b >> n;
        if (a + b + n == 0) break;
        ll F[2][2] = { 1,1,1,0 };
        power(F, n - 1);
        ll nth = F[0][0], n_1th = F[1][0];
        if (n != 1) n_1th += nth;
        cout << a * nth + b * n_1th << '\n';
    }
    return 0;
}