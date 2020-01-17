#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll a, b; cin >> a >> b;
    if (a > b) swap(a, b);
    cout << max(0ll, b - a - 1) << '\n';
    for (ll i = a + 1; i < b; ++i)
        cout << i << ' ';
    return 0;
}