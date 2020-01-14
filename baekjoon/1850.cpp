#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll Euclid(ll m, ll n)
{
    if (m == 0) return n;
    return Euclid(n % m, m);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll n, m;
    cin >> n >> m;
    ll gcd = Euclid(n, m);
    while (gcd--) cout << 1;
    return 0;
}