#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;

ll cache[40][40];
ll nCr(int n, int r)
{
    if (n == r || r == 0) return 1;
    ll& ret = cache[n][r];
    if (ret) return ret;
    return ret = nCr(n - 1, r - 1) + nCr(n - 1, r);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, r; cin >> n >> r;
    r -= n;
    cout << nCr(n + r - 1, r);
    return 0;
}