#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

map<ll, ll> cache;
ll p, q;

// Top_Down으로 풀쟈
ll Infi(ll i)
{
    if (i == 0) return 1;
    auto it = cache.find(i);
    if (it != cache.end()) return (*it).second;
    ll ret = Infi(i / p) + Infi(i / q);
    cache[i] = ret;
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll n;
    cin >> n >> p >> q;
    cout << Infi(n);
    return 0;
}